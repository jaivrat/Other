#include <iostream>


/*Given a sorted array, find if two numbers sum to some number K */

int a[] = {1, 4, 4, 5, 7, 8, 10, 15, 55};


bool ifTwoSumToK(int *a, int len, int k)
{
  int i = 0;
  int j = len-1;
  while(j>i)
  {
	  //invariant that any i' < i and any j'>j ruled out
	  if(a[i] + a[j] == k){
		  return(true);
	  }

	  if(a[i] + a[j] < k){
		  i = i + 1;
	  } else {
            //here a[i] + a[j] > K
	     j = j -1;
	  }
  }

  return(false);
}

int main()
{
  int k = 56;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 12;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 14;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 15;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 16;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 17;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 30;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
  k = 57;
  std::cout << "Testing for k = " << k  << " :" <<  ifTwoSumToK(a, 9, k) << std::endl;
}
