#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <windows.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 24;               // max number of columns in the arena
const int MAXZOMBIES = 100;           // max number of zombies allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Zombie declaration.

class Zombie
{
  public:
      // Constructor
    Zombie(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int m_nOfPBrains;
    bool canMove;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonedBrain();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zombieCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfZombiesAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addZombie(int r, int c);
    bool addPlayer(int r, int c);
    void moveZombies();

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zombie* m_zombies[MAXZOMBIES];
    int     m_nZombies;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;
    int    m_turns;

      // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////

Zombie::Zombie(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A zombie must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_nOfPBrains = 0;
    canMove = true;
}

int Zombie::row() const
{
    return m_row;
}

int Zombie::col() const
{
    return m_col;
}

bool Zombie::isDead() const
{
    if (m_nOfPBrains >= 2) {
      return true;
    }
    return false;
}

void Zombie::move()
{
    if (m_nOfPBrains == 1) {
      if (canMove == false) {  
        canMove = true;
        return;
      }
      canMove = false;
    }
    int dir = randInt(0, NUMDIRS-1);
    //Eats poison brain and this turn it doesnt not move
    if (attemptMove(*m_arena, dir, m_row, m_col)) {
      if (m_arena->player()->row() == m_row && m_arena->player()->col() == m_col) {
          m_arena->player()->setDead();
      }
      if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON) {
        canMove = false;
        m_nOfPBrains++;
        m_arena->setCellStatus(m_row, m_col, EMPTY);
        return;
      }
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropPoisonedBrain()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned brain at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned brain has been dropped.";
}

string Player::move(int dir)
{

      if (attemptMove(*m_arena, dir, m_row, m_col)) {
        if (m_arena->numberOfZombiesAt(m_row, m_col) > 0) {
          setDead();
          return "Player walked into a zombie and died.";
        }
        switch (dir) {
          case NORTH:
            return "Player moved north.";
            break;
          case EAST:
            return "Player moved east.";
            break;
          case SOUTH:
            return "Player moved south.";
            break;
          case WEST:
            return "Player moved west.";
            break;
        }
      }
      return "Player couldn't move; player stands.";  // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nZombies = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    delete m_player;
    for (int i = 0; i < m_nZombies; i++) {
      delete m_zombies[i];
    }

}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::zombieCount() const
{
    return m_nZombies;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfZombiesAt(int r, int c) const
{
      int count = 0;
      for (int i = 0; i < m_nZombies; i++) {
        if (m_zombies[i]->row() == r && m_zombies[i]->col() == c) {
          count++;
        }
      }
      return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned brains)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      for (int i = 0; i < m_nZombies; i++) {
      if (numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) >= 9) {
        displayGrid[m_zombies[i]->row() - 1][m_zombies[i]->col() - 1] = '9';
      } else if (numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) >= 2 && numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) < 9) {
        displayGrid[m_zombies[i]->row() - 1][m_zombies[i]->col() - 1] = numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) + '0';
      } else {
        displayGrid[m_zombies[i]->row() - 1][m_zombies[i]->col() - 1] = 'Z';
      }
    }
    
      // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? '#' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, zombie, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addZombie(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a zombie on a spot with a poisoned brain
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a zombie on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

    // If there are MAXZOMBIES existing zombies, return false.  Otherwise,
      // dynamically allocate a new zombie at coordinates (r,c).  Save the
      // pointer to newly allocated zombie and return true.

    if (m_nZombies == MAXZOMBIES) {
      return false;
    } else {
      m_zombies[m_nZombies] = new Zombie(this, r, c);
      m_nZombies++;
      return true;
    }
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a zombie
    if (numberOfZombiesAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveZombies()
{
      // Move all zombies
      int i = 0;
      while (i < m_nZombies) {
        m_zombies[i]->move();
        if (m_zombies[i]->isDead()) {
          delete m_zombies[i];
          m_nZombies--;
          for (int j = i; j < m_nZombies; j++) {
              m_zombies[j] = m_zombies[j + 1];
          }
        } else {
          i++;
        }
      }
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies < 0)
    {
        cout << "***** Cannot create Game with negative number of zombies!" << endl;
        exit(1);
    }
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
             << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nZombies - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small to hold a player and "
             << nZombies << " zombies!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with zombies
    while (nZombies > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addZombie(r, c);
        nZombies--;
    }

    m_turns = 0;
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedBrain();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonedBrain();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->zombieCount() > 0)
    {
        m_turns++;
        string msg = takePlayerTurn();
        if ( ! player->isDead())
            m_arena->moveZombies();
        m_arena->display(msg);
        cout << m_turns << " turns have been taken." << endl;
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device ran;
    static default_random_engine generator(ran());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    switch (dir) {
      case NORTH:
        if (r > 1) {  
          r--;  
          return true;
        }
        break;
      case EAST:
        if (c < a.cols()) {
          c++;
          return true;
        }
        break;
      case SOUTH:
        if (r < a.rows()) {
          r++;
          return true;
        }
        break;
      case WEST:
        if (c > 1) {
          c--;
          return true;
        }
        break;
    }
    return false;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned brain and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // TODO:  Implement this function
    // Delete the following line and replace it with your code.
    int dangerlvlAhead[4] = {0, 0, 0, 0};
    int lowdangerlvl = 0;
    bool zDir[4] = {false , false , false, false};
    if (r - 1 >= 1 && a.numberOfZombiesAt(r - 1, c) > 0) {
      zDir[NORTH] = true;
      dangerlvlAhead[NORTH] = 99999;
    }
    if (c + 1 <= a.cols() && a.numberOfZombiesAt(r, c + 1) > 0) {
      zDir[EAST] = true;
      dangerlvlAhead[EAST] = 99999;
    }
    if (r + 1 <= a.rows() && a.numberOfZombiesAt(r + 1, c) > 0) {
      zDir[SOUTH] = true;
      dangerlvlAhead[SOUTH] = 99999;
    }
    if (c - 1 >= 1 && a.numberOfZombiesAt(r, c - 1) > 0) {
      zDir[WEST] = true;
      dangerlvlAhead[WEST] = 99999;
    }
    //Checks if theres no zombie surrounding you or if you are surrounded, best bet is to just stay still for both
    if (!(zDir[NORTH] || zDir[EAST] || zDir[SOUTH] || zDir[WEST]) || 
          (zDir[NORTH] && zDir[EAST] && zDir[SOUTH] && zDir[WEST]))
      return false;
    for (int i = 0; i < 4; i++) {
    bool isWall = false;
      if (i == NORTH && r <= 1) isWall = true;
      if (i == EAST  && c >= a.cols()) isWall = true;
      if (i == SOUTH && r >= a.rows()) isWall = true;
      if (i == WEST  && c <= 1) isWall = true;

      if (isWall) {
          dangerlvlAhead[i] = 99999; 
          continue;
      }
      if (zDir[i]) {
        continue;
      } else {
        switch (i) {
          case NORTH:
            //r - 1, c
            if (r - 2 >= 1 && a.numberOfZombiesAt(r - 2, c) > 0) {
              dangerlvlAhead[NORTH] += a.numberOfZombiesAt(r - 2, c);
            }
            if (c - 1 >= 1 && a.numberOfZombiesAt(r - 1, c - 1) > 0) {
              dangerlvlAhead[NORTH] += a.numberOfZombiesAt(r - 1, c - 1);
            }
            if (c + 1 <= a.cols() && a.numberOfZombiesAt(r - 1, c + 1) > 0) {
              dangerlvlAhead[NORTH] += a.numberOfZombiesAt(r - 1, c + 1);
            }
            continue;
          case EAST:
            //r, c + 1
            if (c + 2 <= a.cols() && a.numberOfZombiesAt(r , c + 2) > 0) {
              dangerlvlAhead[EAST] += a.numberOfZombiesAt(r, c + 2);
            }
            if (r - 1 >= 1 && a.numberOfZombiesAt(r - 1, c + 1) > 0) {
              dangerlvlAhead[EAST] += a.numberOfZombiesAt(r - 1, c + 1);
            }
            if (r + 1 <= a.rows() && a.numberOfZombiesAt(r + 1, c + 1) > 0) {
              dangerlvlAhead[EAST] += a.numberOfZombiesAt(r + 1, c + 1);
            }
            continue;
          case SOUTH:
            //r + 1, c
            if (r + 2 <= a.rows() && a.numberOfZombiesAt(r + 2, c) > 0) {
              dangerlvlAhead[SOUTH] += a.numberOfZombiesAt(r + 2, c);
            }
            if (c - 1 >= 1 && a.numberOfZombiesAt(r + 1, c - 1) > 0) {
              dangerlvlAhead[SOUTH] += a.numberOfZombiesAt(r + 1, c - 1);
            }
            if (c + 1 <= a.cols() && a.numberOfZombiesAt(r + 1, c + 1) > 0) {
              dangerlvlAhead[SOUTH] += a.numberOfZombiesAt(r + 1, c + 1);
            }
            continue;
          case WEST:
            //r, c - 1
            if (c - 2 >= 1 && a.numberOfZombiesAt(r , c - 2) > 0) {
              dangerlvlAhead[WEST] += a.numberOfZombiesAt(r, c - 2);
            }
            if (r - 1 >= 1 && a.numberOfZombiesAt(r - 1, c - 1) > 0) {
              dangerlvlAhead[WEST] += a.numberOfZombiesAt(r - 1, c - 1);
            }
            if (r + 1 <= a.rows() && a.numberOfZombiesAt(r + 1, c - 1) > 0) {
              dangerlvlAhead[WEST] += a.numberOfZombiesAt(r + 1, c - 1);
            }
            continue;
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      if (!zDir[i]) {
        bestDir = i;
        break;
      }
    }

    for (int i = 0; i < 4; i++) {
      if (dangerlvlAhead[i] < dangerlvlAhead[bestDir])  
        bestDir = i;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////
void doBasicTests();
#include <type_traits>
#include <cstdlib>
#include <cassert>

#define CHECKTYPE(c, f, r, a)  \
    static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
       "FAILED: You changed the type of " #c "::" #f);  \
    { [[gnu::unused]] auto p = static_cast<r (c::*) a>(&c::f); }

void thisFunctionWillNeverBeCalled()
{
      // If the student deleted or changed the interfaces to the public
      // functions, this won't compile.  (This uses magic beyond the scope
      // of CS 31.)

    Zombie z(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(Zombie, row, int, () const);
    CHECKTYPE(Zombie, col, int, () const);
    CHECKTYPE(Zombie, isDead, bool, () const);
    CHECKTYPE(Zombie, move, void, ());

    Player p(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(Player, row, int, () const);
    CHECKTYPE(Player, col, int, () const);
    CHECKTYPE(Player, isDead, bool, () const);
    CHECKTYPE(Player, dropPoisonedBrain, string, ());
    CHECKTYPE(Player, move, string, (int));
    CHECKTYPE(Player, setDead, void, ());

    Arena a(1, 1);
    CHECKTYPE(Arena, rows, int, () const);
    CHECKTYPE(Arena, cols, int, () const);
    CHECKTYPE(Arena, player, Player*, () const);
    CHECKTYPE(Arena, zombieCount, int, () const);
    CHECKTYPE(Arena, getCellStatus, int, (int,int) const);
    CHECKTYPE(Arena, numberOfZombiesAt, int, (int,int) const);
    CHECKTYPE(Arena, display, void, (string) const);
    CHECKTYPE(Arena, setCellStatus, void, (int,int,int));
    CHECKTYPE(Arena, addZombie, bool, (int,int));
    CHECKTYPE(Arena, addPlayer, bool, (int,int));
    CHECKTYPE(Arena, moveZombies, void, ());

    Game g(1,1,1);
    CHECKTYPE(Game, play, void, ());
}

void findTheZombie(const Arena& a, int& r, int& c)
{
    if      (a.numberOfZombiesAt(r-1, c) == 1) r--;
    else if (a.numberOfZombiesAt(r+1, c) == 1) r++;
    else if (a.numberOfZombiesAt(r, c-1) == 1) c--;
    else if (a.numberOfZombiesAt(r, c+1) == 1) c++;
    else assert(false);
}

void surroundWithPoison(Arena& a, int r, int c)
{
    a.setCellStatus(r-1, c, HAS_POISON);
    a.setCellStatus(r+1, c, HAS_POISON);
    a.setCellStatus(r, c-1, HAS_POISON);
    a.setCellStatus(r, c+1, HAS_POISON);
}

void doBasicTests()
{
    {
        Arena a(10, 20);
        assert(a.addPlayer(2, 5));
        Player* pp = a.player();
        assert(pp->row() == 2  &&  pp->col() == 5  && ! pp->isDead());
        assert(pp->move(NORTH) == "Player moved north.");
        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
        assert(pp->move(NORTH) == "Player couldn't move; player stands.");
        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 5  && pp->isDead());
    }
    {
        Arena a(10, 20);
        int r = 8;
        int c = 18;
        assert(a.addPlayer(r, c));
        for (int k = 0; k < MAXZOMBIES/4; k++)
        {
            assert(a.addZombie(r-1, c));
            assert(a.addZombie(r+1, c));
            assert(a.addZombie(r, c-1));
            assert(a.addZombie(r, c+1));
        }
        assert(! a.player()->isDead());
        a.moveZombies();
        assert(a.player()->isDead());
    }
    {
        Arena a(10, 20);
        int r = 4;
        int c = 4;
        assert(a.addZombie(r, c));
        surroundWithPoison(a, r, c);
        assert(a.addPlayer(8, 18));
        assert(a.zombieCount() == 1  &&  a.numberOfZombiesAt(r, c) == 1);
        a.moveZombies();
        assert(a.zombieCount() == 1  &&  a.numberOfZombiesAt(r, c) == 0);
        findTheZombie(a, r, c);
        assert(a.getCellStatus(r, c) != HAS_POISON);
        a.moveZombies();
        assert(a.zombieCount() == 1  &&  a.numberOfZombiesAt(r, c) == 1);
        a.moveZombies();
        assert(a.zombieCount() == 1  &&  a.numberOfZombiesAt(r, c) == 0);
        findTheZombie(a, r, c);
        a.moveZombies();
        assert(a.zombieCount() == 1  &&  a.numberOfZombiesAt(r, c) == 1);
        surroundWithPoison(a, r, c);
        a.moveZombies();
        assert(a.zombieCount() == 0  &&  a.numberOfZombiesAt(r, c) == 0);
        assert(a.numberOfZombiesAt(r-1, c) == 0);
        assert(a.numberOfZombiesAt(r+1, c) == 0);
        assert(a.numberOfZombiesAt(r, c-1) == 0);
        assert(a.numberOfZombiesAt(r, c+1) == 0);
    }
    {
        Arena a(20, 20);
        assert(a.addPlayer(1, 20));
        struct Coord
        {
            int r;
            int c;
        };
        assert(MAXZOMBIES == 100);
        const int NDOOMED = 4;
        Coord doomed[NDOOMED];
        for (int k = 0; k < NDOOMED; k++)
        {
            doomed[k].r = 3;
            doomed[k].c = 5*k+3;
            assert(a.addZombie(doomed[k].r, doomed[k].c));
            surroundWithPoison(a, doomed[k].r, doomed[k].c);
            for (int i = 0; i < MAXZOMBIES/NDOOMED - 1; i++)
                assert(a.addZombie(20, 20));
        }
        assert(!a.addZombie(20, 20));
        assert(a.zombieCount() == MAXZOMBIES);
        a.moveZombies();
        assert(a.zombieCount() == MAXZOMBIES);
        for (int k = 0; k < NDOOMED; k++)
        {
            findTheZombie(a, doomed[k].r, doomed[k].c);
            surroundWithPoison(a, doomed[k].r, doomed[k].c);
        }
        a.moveZombies();
        assert(a.zombieCount() == MAXZOMBIES);
        a.moveZombies();
        assert(a.zombieCount() == MAXZOMBIES - NDOOMED);
        for (int k = 0; k < NDOOMED; k++)
            assert(a.addZombie(20, 20));
        assert(!a.addZombie(20, 20));
          // If the program crashes after leaving this compound statement, you
          // are probably messing something up when you delete a zombie after
          // it dies (or you have mis-coded the destructor).
          //
          // Draw a picture of your m_zombies array before the zombies move,
          // and also note the values of m_nZombies or any other variable you
          // might have that's involved with the number of zombies.  Trace
          // through your code step by step as the zombies move and die,
          // updating the picture according to what the code says, not what
          // you want it to do.  If you don't see a problem then, try tracing
          // through the destruction of the arena.
          //
          // If you execute the code, use the debugger to check on the values
          // of key variables at various points.  If you didn't try to learn
          // to use the debugger, insert statements that write the values of
          // key variables to cerr so you can trace the execution of your code
          // and see the first place where something has gone amiss.  (Comment
          // out the call to clearScreen in Arena::display so that your output
          // doesn't disappear.)
    }
    cout << "Passed all basic tests (as long as when run under g31 there is no further message after this)." << endl;
    exit(0);
}
int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    //Game g(3, 5, 2);

      // Play the game
    //g.play();
    doBasicTests(); // Remove this line after completing test.
    return 0;       // Remove this line after completing test.
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)  // redefined macro in <windows.h>
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = std::getenv("TERM");
    if (term == nullptr  ||  std::strcmp(term, "dumb") == 0)
        std::cout << std::endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;
    }
}

#endif