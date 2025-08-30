# Constant length Window

- find max sum of 3 consecutive elements. arr=[1,2,3,4,5] k=3

       ```

  int n = arr.size();
  int sum = 0, res = INT_MIN;
  int l = 0;

  for (int r = 0; r < n; r++) {
  sum += arr[r]; // add right element

         if (r >= k - 1) {   // window size reached
             res = max(res, sum);   // update result
             sum -= arr[l];         // remove left element
             l++;                   // slide window
         }

  }

  ```

  ```

# Variable length Window

- longest subarray with sum<=k

  int n = arr.size();
  int l = 0, sum = 0, maxLen = 0;

  for (int r = 0; r < n; r++) {
  sum += arr[r]; // include current element in your logic
  //invalid window
  while (sum > k) { // shrink window if > k
  sum -= arr[l];
  l++;
  }
  //valid winndow
  maxLen = max(maxLen, r - l + 1); // update length of valid size window

  }

# No of subarray with sum = k

    no of subarray with sum <=k - no of subarray with sum <= k-1

# shortest len window with (any condition(sum>=k))

    int shortestWindow(vector<int>& arr, int K) {
        int n = arr.size();
        int left = 0, sum = 0, minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // shrink when condition is satisfied
            while (sum >= K) {
                minLen = min(minLen, right - left + 1);
                sum -= arr[left++];
            }
        }

        return (minLen == INT_MAX) ? -1 : minLen;
    }

these all are for non negative integers

what if num can be -ve also ?
