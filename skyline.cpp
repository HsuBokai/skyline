#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;


class Solution {
	public:

typedef map<int, int> view_ds;

		static bool compare_right(vector<int> b1, vector<int> b2) { return b1[1] < b2[1]; }

		void do_left(int l, view_ds& view, vector< vector<int> >& buildings, vector< pair<int, int> >& ret){
			int n = buildings.size();
			//cout << "l:" << l << endl;
			view.insert(pair<int, int>(buildings[l][2], l));
			view_ds::iterator it = view.end();
			it--;
			int max_height = (view.size()==0) ? 0 : it->first;
			//cout<<"max_height:"<<max_height<<endl;
			ret.push_back(pair<int, int>(buildings[l][0], max_height));
		}

		void do_right(int r, view_ds& view, vector< vector<int> >& buildings, vector< pair<int, int> >& ret){
			int n = buildings.size();
			//cout << "r:" << r << endl;
			view_ds::iterator it = view.end();
			if(view.size() > 0) it--;
			while(view.size() > 0 && buildings[it->second][1] <= buildings[r][1]){
				view.erase(it);
				it = view.end();
				if(view.size() > 0) it--;
			}
			int max_height = (view.size()==0) ? 0 : it->first;
			//cout<<"max_height:"<<max_height<<endl;
			ret.push_back(pair<int, int>(buildings[r][1], max_height));
		}

		vector< pair<int, int> > getSkyline(vector <vector<int> >& buildings) {

			vector< pair<int, int> > ret;
			int n = buildings.size();
			if(n==0) return ret;

			//compare c_right(1,buildings);

			vector<int> left;
			vector< vector<int> > rr(buildings);
			for(int i=0; i<n; ++i){
				left.push_back(i);
				rr[i][0] = i;
			}
			sort(rr.begin(), rr.end(), compare_right);
			vector<int> right;
			for(int i=0; i<n; ++i){
				right.push_back(rr[i][0]);
			}

			view_ds view;
			int i = 0, j = 0;
			while(i<n && j<n){
				int l = left[i], r = right[j];
				if(buildings[l][0] < buildings[r][1]){
					do_left(l,view,buildings,ret);
					i++;
				}
				else{
					do_right(r,view,buildings,ret);
					j++;
				}
			}
			for(; i<n; ++i){
				int l = left[i];
				do_left(l,view,buildings,ret);	
			}
			for(; j<n; ++j){
				int r = right[j];
				do_right(r,view,buildings,ret);
			}

			int m = ret.size();
			cout << m << endl;

			vector< pair<int, int> > ret3(1,ret[0]);
			int max_height = 0;
			for(int k=1; k<m; ++k){
				if(ret[k].first != ret[k-1].first){
					ret3.push_back(ret[k]);
					max_height = ret[k].second;
				}
				else{
					max_height = max(ret[k].second, max_height);
					ret3[ret3.size()-1].second = max_height;
				}
			}
			int mm = ret3.size();
			cout << ret3.size() << endl;

			vector< pair<int, int> > ret2(1,ret3[0]);
			for(int k=1; k<mm; ++k){
				if(ret3[k].second != ret3[k-1].second)
					ret2.push_back(ret3[k]);
			}
			cout << ret2.size() << endl;
			//cout << "end" << endl;;
			return ret2;
		}
};

void add_buildings(int left, int right, int height, vector <vector<int> >& buildings){
	int a1[] = {left, right ,height};
	vector<int> b1(a1, a1+3);
	buildings.push_back(b1);
}


int main(){
	Solution s;
	vector< vector<int> > buildings; //= { {2, 9, 10}, 3 7 15], [5 12 12], [15 20 10], [19 24 8] } ;
	//for(int i=1; i<3000; ++i)
	//	add_buildings(i,100000-i,i, buildings);
	
	add_buildings(1,2,1, buildings);
	add_buildings(1,2,2, buildings);
	add_buildings(1,2,3, buildings);

	s.getSkyline(buildings);
	return 0;
}
