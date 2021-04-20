//멀쩔한 사각형

using namespace std;

typedef long long ll;

ll gcd(int a, int b){   
    if(b == 0){
        return a;
    } else{
        return gcd(b, a%b);
    }
}

ll removedCell(int w, int h){
    return w + h - 1;
}

long long solution(int w,int h) {
    long long answer = 0;
    ll g = gcd(w, h);
    ll savedCells = (w/g * h/g) - removedCell(w/g, h/g);
    for(ll i=0; i<g; ++i){
        answer += savedCells;
        answer += (((ll)w/g) * ((ll)h/g)) * i * (ll)2;
    }
    
    return answer;
}