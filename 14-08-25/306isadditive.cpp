//next  time helper should be iterative and string summmation by ur own

class Solution {
public:
    std::string addStrings(std::string num1, std::string num2) {
        std::string result = "";
        int carry = 0;

        // Pointers to the last character of each string
        int i = num1.length() - 1;
        int j = num2.length() - 1;

        // Loop continues as long as there are digits in either string OR a carry remains
        while (i >= 0 || j >= 0 || carry > 0) {
            // Get the integer value of the digit from num1, or 0 if we've run out of digits
            int digit1 = (i >= 0) ? num1[i] - '0' : 0;
            
            // Get the integer value of the digit from num2, or 0 if we've run out of digits
            int digit2 = (j >= 0) ? num2[j] - '0' : 0;

            // Calculate the sum for the current column
            int sum = digit1 + digit2 + carry;
            
            // The new carry is the sum divided by 10
            carry = sum / 10;
            
            // The digit for our result is the remainder
            int current_digit = sum % 10;
            
            // Append the current digit to our result string
            result += std::to_string(current_digit);

            // Move the pointers to the left
            i--;
            j--;
        }

        // The result string was built in reverse order, so we must reverse it
        std::reverse(result.begin(), result.end());
        
        return result;
    }
    bool solve(string& num,int idx,string& prev,string& curr){
        if(idx==num.size()) return true;
        string res=addStrings(prev,curr);
        for(int i=0;i<res.size();i++){
            if(res[i]!=num[idx+i]) return false;
        }
        int n=res.size();
        return solve(num,idx+n,curr,res);
    }
    bool isAdditiveNumber(string num) {
        int n=num.size();
        string prev="";
        for(int i=0;i<n;i++){
            prev+=num[i];
            if(num[0]=='0' && i>0) break;
            string curr="";
            for(int j=i+1;j<n-1;j++){
                curr+=num[j];
                if(curr[0]=='0' && curr.size()>1) break;
                // cout<<prev<<" "<<curr<<endl;
                if(solve(num,j+1,prev,curr)) return true;
            }
        }
        return false;
    }
};

tc- O(n^3)
sc- O(n)


