#include <iostream>
#include <climits>

const int size = 3;

class Game
{
private:
    char board[size][size];
    char *boardPtr = (char *)board;
    char bot, player, turn;
    int bwin = 0, pwin = 0;
    bool isOver = false;

    void initialize()
    {
        int position = 49;

        for (int i = 0; i < size * size; i++)
        {
            *(boardPtr + i) = position;
            position++;
        }
    }

    void print()
    {
        for (int i = 0; i < size * size; i++)
        {
            std::cout << "|";
            std::cout << *(boardPtr + i) << "|";
            if ((i + 1) % size == 0)
            {
                std::cout << std::endl;
                std::cout << "+-++-++-+" << std::endl;
            }
        }
    }

    bool isInRange(char s)
    {
        if (s >= '/' &&
            s <= ':')
        {
            return true;
        }
        return false;
    }

    char gameOver()
    {
        // row
        for (int i = 0; i < size; i++)
        {
            if (board[i][0] == board[i][1] &&
                board[i][1] == board[i][2])
            {
                isOver = true;
                return board[i][0];
            }
            if (board[0][i] == board[1][i] &&
                board[1][i] == board[2][i])
            {
                isOver = true;
                return board[0][i];
            }
        }

        // cross
        if (board[0][0] == board[1][1] &&
            board[1][1] == board[2][2])
        {
            isOver = true;
            return board[0][0];
        }
        if (board[0][2] == board[1][1] &&
            board[1][1] == board[2][0])
        {
            isOver = true;
            return board[0][2];
        }

        for (int i = 0; i < size * size; i++)
        {
            if (*(boardPtr + i) != player &&
                *(boardPtr + i) != bot)
            {
                isOver = false;
                return ',';
            }
        }

        isOver = true;
        return '.';
    }

    int evaluate()
    {
        char winner = gameOver();
        if (winner == player)
            return -10;
        else if (winner == bot)
            return 10;
        return 0;
    }

    int minimax(char b[][size], int depth, bool isMaxmizing)
    {
        gameOver();
        if (isOver)
            return evaluate();

        if (isMaxmizing)
        {
            int bestScore = INT_MIN;
            for (int i = 0; i < size * size; i++)
            {
                if (isInRange(*(boardPtr + i)))
                {
                    char temp = *(boardPtr + i);
                    *(boardPtr + i) = bot;
                    int score = minimax(
                        b,
                        depth + 1,
                        false);
                    *(boardPtr + i) = temp;
                    bestScore = std::max(score, bestScore);
                }
            }
            return bestScore;
        }
        else
        {
            int bestScore = INT_MAX;
            for (int i = 0; i < size * size; i++)
            {
                if (isInRange(*(boardPtr + i)))
                {
                    char temp = *(boardPtr + i);
                    *(boardPtr + i) = player;
                    int score = minimax(
                        b,
                        depth + 1,
                        true);
                    *(boardPtr + i) = temp;
                    bestScore = std::min(score, bestScore);
                }
            }
            return bestScore;
        }
        return 0;
    }

    void makemove()
    {
        int bestScore = -1;
        std::pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < size * size; i++)
        {
            if (isInRange(*(boardPtr + i)))
            {
                char temp = *(boardPtr + i);
                *(boardPtr + i) = bot;
                int score = minimax(board, 0, false);
                *(boardPtr + i) = temp;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i / size, i % size};
                }
            }
        }
        board[bestMove.first][bestMove.second] = bot;
    }

public:
    void run()
    {
        int choose;

        do
        {
            std::cout << "0. exit" << std::endl;
            std::cout << "1. play" << std::endl;
            std::cout << "/: ";
            std::cin >> choose;

            switch (choose)
            {
            case 1:
                initialize();
                print();
                char winner;
                isOver = false;

                do
                {
                    std::cout << "Select one O or X: ";
                    std::cin >> player;

                    if (player == 'X')
                    {
                        bot = 'O';
                    }
                    else
                    {
                        bot = 'X';
                    }
                } while (player != 'O' &&
                         player != 'X');

                while (!isOver)
                {
                    bool endTurn = false;

                    if (turn == bot)
                    {
                        std::cout << "Player (" << bot << ") move!" << std::endl;
                        makemove();
                    }
                    else
                    {
                        char number;
                        std::cout << "Player (" << player << ") move!" << std::endl;
                        std::cout << "Enter position: ";
                        std::cin >> number;

                        for (int i = 0; i < size * size; i++)
                        {
                            if (*(boardPtr + i) == number)
                            {
                                *(boardPtr + i) = player;
                                endTurn = true;
                                break;
                            }
                            else
                            {
                                continue;
                            }

                            if (endTurn)
                            {
                                break;
                            }
                        }
                    }

                    winner = gameOver();
                    turn = (turn == bot) ? player : bot;

                    print();
                }

                if (winner == bot)
                {
                    bwin++;
                    std::cout << winner << " is a winner!" << std::endl;
                }
                else if (winner == player)
                {
                    pwin++;
                    std::cout << winner << " is a winner!" << std::endl;
                }
                else
                {
                    std::cout << "draw" << std::endl;
                }

                std::cout << "Player: " << pwin << " - " << "Bot: " << bwin << std::endl;
            }
        } while (choose != 0);
    }
};

int main()
{
    Game game;
    game.run();
    return 0;
}