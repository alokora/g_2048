#include <bits/stdc++.h>
using namespace std;

int Xn = 0;

int generate_random_no()
{
    Xn = ((75 * Xn) + 74) % (1<<16 | 1);
    return Xn;
}

pair<int, pair<int, int>> getRandom_value_and_place(vector<pair<int, int>> &Empty_cells)
{
    int min = 0, max = (int)Empty_cells.size() - 1;
    int pos = (generate_random_no() % (max - min + 1)) + min;

    sort(Empty_cells.begin(), Empty_cells.end());

    min = 1, max = 10;
    int value = (generate_random_no() % (max - min + 1)) + min;

    if (value <= 8)
        return make_pair(2, Empty_cells[pos]);
    else
    return make_pair(4, Empty_cells[pos]);
}

int board[4][4];
int no_empty_cells;

void print()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(board[i][j] == 0)
                cout<<".  ";
            else
                cout<<board[i][j]<<"  ";
           
        } cout<<"\n";
    }
}

void gravity(vector<int> &arr)
{
    int s = 0;
    for(int i=0; i<4; i++)
    {
        if(arr[i] != 0)
        {
            swap(arr[i], arr[s]);
            s++;
        }
    }
}
void merge(vector<int> &arr)
{
    for(int i=1; i<4; i++)
    {
        if(arr[i] == arr[i-1] && arr[i] != 0)
        {
            arr[i-1] = arr[i-1]*2;
            arr[i] = 0;
            no_empty_cells++;
        }
    }
}
bool push_left(vector<int> &arr)
{
    vector<int> copyArr(arr);
    gravity(arr);
    merge(arr);
    gravity(arr);
    for(int i=0; i<4; i++)
    {
        if(copyArr[i] != arr[i])
            return true;
    }
    return false;
}
bool move(int direction)
{
    bool change = false;
    vector<int> curr;

    
    if (direction == 1)
    {
        for (int i = 0; i < 4; i++)
        {

            for (int j = 0; j < 4; j++)
                curr.push_back(board[i][j]);

            change |= push_left(curr);
            
            for (int j = 3; j >= 0; j--)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }
    else if (direction == 2)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int i = 3; i >= 0; i--)
                curr.push_back(board[i][j]);
            change |= push_left(curr);

            for (int i = 0; i < 4; i++)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }

    else if (direction == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 3; j >= 0; j--)
                curr.push_back(board[i][j]);

            change |= push_left(curr);

            for (int j = 0; j < 4; j++)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }

    else
    {
        for (int j = 0; j < 4; j++)
        {

            for (int i = 0; i < 4; i++)
                curr.push_back(board[i][j]);

            change |= push_left(curr);

            for (int i = 3; i >= 0; i--)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }
    return change;
}

void fill_random_cell()
{
    vector<pair<int, int>> Empty_cells;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                Empty_cells.push_back({i, j});
        }
    }
    auto value_place = getRandom_value_and_place(Empty_cells);
    int val = value_place.first;
    int x = value_place.second.first, y = value_place.second.second;
    board[x][y] = val;
    no_empty_cells--;
}


int check_board()
{
    bool move_is_possible = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2048)
                return 1;
            if (i < 3 && board[i][j] == board[i + 1][j])
                move_is_possible = true;
            if (j < 3 && board[i][j] == board[i][j + 1])
                move_is_possible = true;
        }
    }
    if (no_empty_cells == 0 && (!move_is_possible))
        return 0;
    return 2;
}


void initialize()
{
    memset(board, 0, sizeof(board));
    no_empty_cells = 16;
fill_random_cell();
fill_random_cell();
}
struct game
{
    game(){};

    void play()
    {
        int n; cin >> n;
        initialize();
        print();

        for(int i=0; i<n; i++)
        {
            int step;
            cin >> step;
            bool validMove = move(step);

            if (!validMove)
            {
                cout <<"Invalid Move" << "\n";
                continue;
            }

        generate_random_no();
            print();

            int gameStatus = check_board();

            if (gameStatus == 0)
            {
                cout <<"Game Over, You Lose "<< "\n";
                return;
            }
            else if (gameStatus == 1)
            {
                cout <<"Game Over, You Win"<< "\n";
                return;
            }
        }
    }
};
int main()
{
   game g_2048;
    g_2048.play();
    return 0;
}
