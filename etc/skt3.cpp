#include <vector>
#include <iostream>
#include <string>

#define DIVIDE_NUM 10000019

using namespace std;

void initCellMap(vector<vector<int>> &cellMap, int width, int height){
    for(int hei=0; hei<=height; ++hei){
        vector<int> temp;
        for(int wid=0; wid<=width; ++wid){
            if(hei == 0 || wid == 0){
                temp.push_back(1);
                continue;
            }
            temp.push_back(0);
        }
        cellMap.push_back(temp);
    }
}

void printCellMap(vector<vector<int>> cellMap, int w, int h){
    for(int hei=0; hei<=h; ++hei){
        for(int wid=0; wid<=w; ++wid){
            cout << cellMap[hei][wid] << ' ';
            if(cellMap[hei][wid] < 10){
                cout << "      ";
            } else if(cellMap[hei][wid] < 100){
                cout << "     ";
            } else if(cellMap[hei][wid] < 1000){
                cout << "    ";
            } else if(cellMap[hei][wid] < 10000){
                cout << "   ";
            } else if(cellMap[hei][wid] < 100000){
                cout << "  ";
            } else if(cellMap[hei][wid] < 1000000){
                cout << " ";
            } else if(cellMap[hei][wid] < 10000000){
                cout << "";
            }
        }cout << "\n";
    }
}

int countNums(vector<int> diagonal, int w, int h){
    int diagWid = diagonal[0], diagHei = diagonal[1];
    vector<vector<int>> cellMap;
    initCellMap(cellMap, w, h);
    bool found = false;
    for(int hei=0; hei<=h; ++hei){
        for(int wid=0; wid<=w; ++wid){
            if(cellMap[hei][wid] && found){
                continue;
            }
            if(hei != 0 && wid != 0){
                cellMap[hei][wid] = (cellMap[hei-1][wid] % DIVIDE_NUM) + (cellMap[hei][wid-1] % DIVIDE_NUM);    
            }
            // cellMap[hei][wid] = (cellMap[hei-1][wid] % DIVIDE_NUM) + (cellMap[hei][wid-1] % DIVIDE_NUM);
            cellMap[hei][wid] %= DIVIDE_NUM;
            if(hei == diagHei && wid == (diagWid - 1)){
                if(cellMap[hei][wid]){
                    cout << "fill first " << hei << ", " << wid << "as " << cellMap[hei][wid] << endl;
                    for(int tempHei=hei; tempHei<=h; ++tempHei){
                        cellMap[tempHei][wid] = cellMap[hei][wid] % DIVIDE_NUM;
                    }    
                } else{
                    cout << "fill first " << hei << ", " << wid << "as " << cellMap[hei][wid]*2 << endl;
                    for(int tempHei=hei; tempHei<=h; ++tempHei){
                        cellMap[tempHei][wid] = cellMap[hei][wid]*2 % DIVIDE_NUM;
                    }
                }
                // if(wid == 0){
                //     cout << "fill first " << hei << ", " << wid << "as " << cellMap[hei][wid]*2 << endl;
                //     for(int tempHei=hei; tempHei<=h; ++tempHei){
                //         cellMap[tempHei][wid] = cellMap[hei][wid]*2 % DIVIDE_NUM;
                //     }    
                //     continue;
                // }
                // cout << "fill first " << hei << ", " << wid << "as " << cellMap[hei][wid] << endl;
                // for(int tempHei=hei; tempHei<=h; ++tempHei){
                //     cellMap[tempHei][wid] = cellMap[hei][wid] % DIVIDE_NUM;
                // }
                // found = true;
                continue;
            }
            if(hei == (diagHei - 1) && wid == diagWid){
                if(cellMap[hei][wid]){
                    for(int tempWid=wid; tempWid<=w; ++tempWid){
                        cellMap[hei][tempWid] = cellMap[hei][wid] % DIVIDE_NUM;
                    }    
                } else{
                    for(int tempWid=wid; tempWid<=w; ++tempWid){
                        cellMap[hei][tempWid] = cellMap[hei][wid]*2 % DIVIDE_NUM;
                    }    
                }
                // if(hei == 0){
                //     cout << "fill second " << hei << ", " << wid << "as " << cellMap[hei][wid]*2 << endl;
                //     for(int tempWid=wid; tempWid<=w; ++tempWid){
                //         cellMap[hei][tempWid] = cellMap[hei][wid]*2 % DIVIDE_NUM;
                //     }    
                // }
                // cout << "fill second " << hei << ", " << wid << "as " << cellMap[hei][wid] << endl;
                // for(int tempWid=wid; tempWid<=w; ++tempWid){
                //     cellMap[hei][tempWid] = cellMap[hei][wid] % DIVIDE_NUM;
                // }
                found = true;
                continue;
            }
        }
    }
    cout << "return " << cellMap[h][w] << "\n";
    printCellMap(cellMap, w, h);
    cout << "\n";
    return cellMap[h][w] % DIVIDE_NUM;
}

int solution(int width, int height, vector<vector<int>> diagonals) {
    int answer = 0;
    vector<vector<int>> vec;
    for(auto diagonal : diagonals){
        answer += countNums(diagonal, width, height);
    }
    return answer;
}

int main(void){
    vector<vector<int>> temp;
    vector<int> t;
    t.push_back(1);
    t.push_back(1);
    temp.push_back(t);
    vector<int> p;
    p.push_back(2);
    p.push_back(2);
    temp.push_back(p);
    solution(2, 2, temp);

    return 0;
}