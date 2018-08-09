#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<int> VI;
void Search(VI& arr, int des)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == des)
        {
            cout << "index:" << i << endl;
        }
    }
    return ;
}
int main()
{
    int a[] =  {1, 4, 7, 5, 9, 3};
    VI arr(a, a + 6);
    Search(arr, 3);
    return 0;
}
