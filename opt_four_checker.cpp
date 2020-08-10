#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<map>
#include<string>

using namespace std;

int dist(pair<int, int> x, pair<int, int> y){
    return abs(x.first - y.first)+abs(x.second - y.second);
}

int distf(pair<int, int> x, pair<int, int> y, pair<int, int> x1, pair<int, int> y1){
    return min(dist(x, y), min(dist(x, x1)+dist(y1, y)+1, dist(x, y1)+dist(x1, y)+1));
}

bool corner_check(pair<int, int> x, int n, int m){
    pair<int, int> p(1, 1), q(1, m), r(n, m), s(n, 1);
    return x != p && x != q && x != r && x != s;
}

bool four_cond(pair<int, int> x1, pair<int, int> y1, int n, int m){
    int Gain1 = abs(abs(x1.second - y1.second) - abs(x1.first - y1.first)) - 1;
    
    bool first = corner_check(x1, n, m) && corner_check(y1, n, m);
    bool second = (Gain1 % 2 == 0) && (Gain1 > 0);
    bool third = 2 * min(abs(y1.first - x1.first), abs(x1.second - y1.second)) >= (Gain1 + 4);
    return first && second && third;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout<<"Please provide dimensions of the grid.\n";
        exit(-1);
    }
    int n = stoi(argv[1]);
    int m = stoi(argv[2]);
    vector< pair<int, int> > points, border_points;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            pair<int, int> p(i, j);
            points.push_back(p);
            if(i == 1 || j == 1 || i == n || j == m)
                border_points.push_back(p);
        }
    }
    cout<<border_points.size()<<endl;

    vector< pair< pair<int, int>, pair<int, int> > > point_pairs;

    for (int i = 0; i < points.size(); i++){
        for (int j = i+1; j < points.size(); j++){
            pair< pair<int, int>, pair<int, int> > p(points[i], points[j]);
            point_pairs.push_back(p);
        }
    }

    vector< tuple<pair<int, int>, pair<int, int>, pair<int, int> > > three_border_points;

    for (int i = 0; i < border_points.size(); i++){
        for (int j = i+1; j < border_points.size(); j++){
            for(int k = j+1; k < border_points.size(); k++){
                tuple< pair<int, int>, pair<int, int>, pair<int, int> > tup;
                tup = make_tuple(border_points[i], border_points[j], border_points[k]);
                three_border_points.push_back(tup);
            }
        }
    }
            
    for (int i = 0; i < point_pairs.size(); i++){
        pair<int, int> x = point_pairs[i].first, y = point_pairs[i].second;
        if(dist(x, y) > 1 && (x.first <= y.first) && (x.second >= y.second) && (x.second - y.second) >= (y.first - x.first)){
            bool found = true;
            for(int j = 0; j < three_border_points.size(); j++){
                map< tuple <int, int, int>, int> distances;
                bool flag = true;
                for (int t = 0; t < points.size(); t++){
                    tuple<int, int, int> tup;
                    tup = make_tuple(distf(points[t], get<0>(three_border_points[j]), x, y), distf(points[t], get<1>(three_border_points[j]), x, y), distf(points[t], get<2>(three_border_points[j]), x, y));
                    if(distances.count(tup) > 0){
                        flag = false;
                        break;
                    }
                    else
                        distances[tup] = 1;
                }
                if(flag){
                    found = false;
                    break;
                }   
            }
            bool cond = four_cond(x, y, n, m);
            if(!(cond ^ found)){
                if(found)
                    cout<<"MD is 4 when edge is between ("<<x.first<<","<<x.second<<") and ("<<y.first<<","<<y.second<<")\n";
            }
            else{
                cout<<"Mistake\n";
                exit(-1);
            }
        }
    }
    cout<<"Success!\n";
}