//it is here for processing the range sum query
vector<int>segTree;

//Building... 
//Requirements :-
//1. array arr
//2. array segTree
//3. range [start, end]
//4. index of segTree
void build(vector<int>&arr, int start, int end, int index){
	//TC => O[2*n] => n + n/2 + n/4....
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

//updating...
//Requirements :-
//1. array arr
//2. array segTree
//3. range [start, end]
//4. index
//5. position
//6. value
void update(vector<int>&arr, int start, int end, int index, int pos, int value){
	//TC = O[logn] => eliminating the half part each time
	if(start == end){
		arr[pos] = value;
		segTree[index] = arr[pos];
		return;
	}

	int mid = (start + end)/2;
	int left = 2*index, right = 2*index+1;
	if(mid >= pos){ // go to left
		update(arr, start, mid, left, pos, value);
	}else{ // go to right
		update(arr, mid+1, end, right, pos, value);
	}

	//also update at each point after updating in original array
	segTree[index] = segTree[left] +segTree[right];
}

//Queries...
//Requirements :-
//1. array arr
//2. array segTree
//3. node range [start, end]
//4. ques range [l, r]
//5. index
int query(vector<int>&arr, int start, int end, int l, int r, int index){
	//TC = 4*O[logn] => Atmost 4 nodes to be processes across each level 
	//at max 1 partial overlap only

	//complete overlap -> return node value = O[1]
		//[l, start, end, r]
	if(l <= start && r >= end){
		return segTree[index];
	}

	//complete disjoint -> return 0 in this range sum query case = O[1]
	if(l > end || r < start){
		return 0;
	}

	//partial overlap -> return left + right
	int mid = (start+ end)/2;
	int left = 2*index, right = 2*index+1;
	int leftAnswer = query(arr,start, mid, l, r,left);
	int rightAnswer = query(arr, mid+1, end, l, r, right);
	return leftAnswer + rightAnswer;
}

void solve(){
   //Taking the array input and processing the range queries in efficient
   //time using the segment trees concept
    int n;
    cin >> n;
    vector<int>arr(n);
    for(int i =0;i<n; i++){
   	   cin >> arr[i];
    }
    if(!((n)&(n-1))){
       //n is power of two then segmentTree array size is 2*n -1 
   	   segTree.resize(2*n, 0);
    }else{
    	// n is not a power of two then make it to the next closest power of two
    	//it will be always <= 2*n then now newN = 2*n
    	//size of the segTree is 2*(2n)-1 = 4n-1
   	   segTree.resize(4*n, 0);
    }

    //if(0 based indexing) => left = 2*index+1, right = 2*n +2
    //else if(1 based indexing) => left = 2*index, right = 2*index+1
    //Here using the 1 based indexing

    build(arr, 0, n-1, 1);
    dbg(segTree)

    cout << query(arr, 0, n-1, 0, 3, 1) << "\n"; // 1 2 2 1 3 1 2 1

    update(arr, 0, n-1, 1, 3, 3);
    dbg(segTree)

    cout << query(arr, 0, n-1, 0, 3, 1) << "\n"; // 1 2 2 3 3 1 2 1
}
