// zombies.cpp

// Portions that you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.
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
    // I THINK ITS DONE  
    // TODO:
      //   Return without moving if the zombie has eaten one poisoned
      //   brain (so is supposed to move only every other turn) and
      //   this is a turn it does not move.

      //   Otherwise, attempt to move in a random direction; if can't
      //   move, don't move.  If it lands on a poisoned brain, eat the
      //   brain and remove it from the game (so it is no longer on that
      //   grid point).

      //   This illustrates how you can select a random direction:
      //   int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
      int dir = randInt(0, NUMDIRS-1);
      //Eats poison brain and this turn it doesn not move
      if (m_arena->getCellStatus(m_row, m_col) == '*') {
        canMove == false;
        m_nOfPBrains++;
        m_arena->setCellStatus(m_row, m_col, EMPTY);
        return;
      }
      //If step first move after eating poison brain don't move, then alternate
      if (canMove == false) {
        canMove = true;
        return;
      }
      //Attempt to move
      attemptMove(*m_arena, dir, m_row, m_col); 
      //If eaten poison brain
      if (m_nOfPBrains == 1) {
        canMove == false;
        return;
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
    // TODO:  Attempt to move the player one step in the indicated
      //        direction.  If this fails,
      //        return "Player couldn't move; player stands."
      //        If the player moves onto a zombie, the player dies and this
      //        returns "Player walked into a zombie and died."
      //        Otherwise, return one of "Player moved north.",
      //        "Player moved east.", "Player moved south.", or
      //        "Player moved west."
      return "Player couldn't move; player stands.";  // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    if (m_arena->numberOfZombiesAt(m_row, m_col) >= 1) {
      return true;
    }
    return false;
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

      // Indicate each zombie's position
    for (int i = 0; i < m_nZombies; i++) {
      if (numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) >= 9) {
        displayGrid[m_zombies[i]->row() - 1][m_zombies[i]->col() - 1] = '9';
      } else if (numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) >= 2 || numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col()) < 9) {
        displayGrid[m_zombies[i]->row() - 1][m_zombies[i]->col() - 1] = numberOfZombiesAt(m_zombies[i]->row(), m_zombies[i]->col());
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
        if (m_zombies[i]->isDead()) {
          delete m_zombies[i];
          m_nZombies--;
          for (int j = i; j < m_nZombies; j++) {
              m_zombies[j] = m_zombies[j + 1];
          }
        } else {
          m_zombies[i]->move();
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
      // TODO:  Implement this function
      // Delete the following line and replace it with the correct code.
    return false;  // This implementation compiles, but is incorrect.
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned brain and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
      // TODO:  Implement this function
      // Delete the following line and replace it with your code.
    return false;  // This implementation compiles, but is incorrect.

      // Your replacement implementation should do something intelligent.
      // You don't have to be any smarter than the following, although
      // you can if you want to be:  If staying put runs the risk of a
      // zombie possibly moving onto the player's location when the zombies
      // move, yet moving in a particular direction puts the player in a
      // position that is safe when the zombies move, then the chosen
      // action is to move to a safer location.  Similarly, if staying put
      // is safe, but moving in certain directions puts the player in
      // danger of dying when the zombies move, then the chosen action should
      // not be to move in one of the dangerous directions; instead, the player
      // should stay put or move to another safe position.  In general, a
      // position that may be moved to by many zombies is more dangerous than
      // one that may be moved to by few.
      //
      // Unless you want to, you do not have to take into account that a
      // zombie might be poisoned and thus sometimes less dangerous than one
      // that is not.  That requires a more sophisticated analysis that
      // we're not asking you to do.
}


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(3, 5, 2);

      // Play the game
    g.play();
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