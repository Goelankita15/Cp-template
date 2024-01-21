#include<bits/stdc++.h>
using namespace std;

vector<int> segTree, lazy;// just like segment Tree a lazy array
void build(vector<int>&arr, int start, int end, int index){
	if(start == end){
		segTree[index] = arr[start];
		return;
	}

	int mid = (start + end)/2;
	int left = 2*index, right = 2*index +1 ;
	build(arr, start, mid, left);
	build(arr, mid+1, end, right);
	segTree[index] = segTree[left] + segTree[right];
}
//updation of adding a value in range[l:r] in array in O[logn] time using lazy propagation
void update(vector<int>&arr, int start, int end, int index, int l,int r,  int value){

	//checking if index is lazy if yes then 
	//update the seg index 
	// and mark its child lazy if exists
	if(lazy[index] != 0){
		segTree[index] = (end-start+1)*lazy[index];
		if(start != end){
			lazy[2*index] += lazy[index];
			lazy[2*index+1] += lazy[index];
		}
		lazy[index] =0;
	}

	//if complete overlap
	//just make the index of segTree with newvalue
	if(start >= l && r >= end){
		segTree[index] += (end-start+1)*value;
		if(start != end){ // mark its children lazy
			lazy[2*index] += value;
			lazy[2*index+1] += value;
		}
		return;
	}

	//if(disjoint)
	if(l > end || r < start){
		return;
	}

	int mid = (start + end)/2;
	int left = 2*index, right = 2*index+1;
	update(arr, start, mid, left, l, r, value);
	update(arr, mid+1, end, right, l, r, value);

	segTree[index] = segTree[left] +segTree[right];
}
int query(vector<int>&arr, int start, int end, int l, int r, int index){
	//if lazy index is not equal to zero update the value 
	if(lazy[index] != 0){
		segTree[index] = (end-start+1)*lazy[index];
		if(start != end){
			lazy[2*index] += lazy[index];
			lazy[2*index+1] += lazy[index];
		}
		lazy[index] =0;
	}

	//complete overlap
	if(l <= start && r >= end){
		return segTree[index];
	}

	//No overlap
	if(l > end || r < start){
		return 0;
	}

	//partial overlap
	int mid = (start+ end)/2;
	int left = 2*index, right = 2*index+1;
	int leftAnswer = query(arr,start, mid, l, r,left);
	int rightAnswer = query(arr, mid+1, end, l, r, right);
	return leftAnswer + rightAnswer;
}
int main(){
	int n;
   cin >> n;
   vector<int>arr(n);
   for(int i =0;i<n; i++){
   	cin >> arr[i];
   }
	if(!((n)&(n-1))){
	   	segTree.resize(2*n, 0);
	   	lazy.resize(2*n, 0);
	   }else{
	   	segTree.resize(4*n, 0);
	   	lazy.resize(4*n, 0);
	   }

	   build(arr, 0, n-1, 1);
	   update(arr, 0, n-1, 1, 1, 6, 5);
	   cout<< query(arr, 0, n-1,1, 6, 1) << "\n";

	   	// cout<< query(arr, 0, n-1,1, 6, 1)+ 6*5 << "\n"; 
	   	// this question can be solved without lazy propagation
	return 0;
}