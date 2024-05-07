#include <iostream>
#include <climits>

const int size = 3;

char board[size][size];
char bot = 'X', player = 'O', turn;
bool isOver = false;

void initialize()
{
    int position = 49;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            board[i][j] = position;
            position++;
        }
    }
}

void print()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << "|";
            std::cout << board[i][j] << "|";
        }
        std::cout << std::endl;
        std::cout << "+-++-++-+" << std::endl;
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

    // col
    for (int i = 0; i < size; i++)
    {
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

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] != player &&
                board[i][j] != bot)
            {
                isOver = false;
                return ',';
            }
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
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (isInRange(b[i][j]))
                {
                    char temp = b[i][j];
                    b[i][j] = bot;
                    int score = minimax(
                        b,
                        depth + 1,
                        false);
                    b[i][j] = temp;
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (isInRange(b[i][j]))
                {
                    char temp = b[i][j];
                    b[i][j] = player;
                    int score = minimax(
                        b,
                        depth + 1,
                        true);
                    b[i][j] = temp;
                    bestScore = std::min(score, bestScore);
                }
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

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (isInRange(board[i][j]))
            {
                char temp = board[i][j];
                board[i][j] = bot;
                int score = minimax(board, 0, false);
                board[i][j] = temp;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    board[bestMove.first][bestMove.second] = bot;
}

int main()
{
    int choose;

    do
    {
        std::cout << "0. exit" << std::endl;
        std::cout << "1. single-player" << std::endl;
        std::cout << "/: ";
        std::cin >> choose;

        switch (choose)
        {
        case 1:
            initialize();
            print();
            char winner;
            isOver = false;

            while (!isOver)
            {
                bool endTurn = false;

                if (turn == 'X')
                {
                    std::cout << "Player (X) move!" << std::endl;
                    makemove();
                }
                else
                {
                    char number;
                    std::cout << "Player (O) move!" << std::endl;
                    std::cout << "Enter position: ";
                    std::cin >> number;

                    for (int i = 0; i < size; ++i)
                    {
                        for (int j = 0; j < size; ++j)
                        {
                            if (board[i][j] == number)
                            {
                                board[i][j] = player;
                                endTurn = true;
                                break;
                            }
                            else
                            {
                                continue;
                            }
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

            if (winner == bot ||
                winner == player)
            {
                std::cout << winner << " is a winner" << std::endl;
            }
            else
            {
                std::cout << "draw" << std::endl;
            }
            break;
        }
    } while (choose != 0);

    return 0;
}