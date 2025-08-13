#Expression add operators

class Solution {
public:
// Define our new data type for clarity
using number_t = long long;

// Helper function to determine operator precedence (unchanged)
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// applyOp now works with long long and includes overflow checks
number_t applyOp(number_t a, number_t b, char op) {
    const number_t LL_MAX = std::numeric_limits<long long>::max();
    const number_t LL_MIN = std::numeric_limits<long long>::min();

    switch (op) {
        case '+':
            // Overflow check: if b > 0 and a is already greater than MAX - b, it will overflow.
            if (b > 0 && a > LL_MAX - b) throw std::overflow_error("Addition overflow");
            // Underflow check for negative numbers
            if (b < 0 && a < LL_MIN - b) throw std::overflow_error("Addition underflow");
            return a + b;
        case '-':
            // Overflow check
            if (b < 0 && a > LL_MAX + b) throw std::overflow_error("Subtraction overflow");
            // Underflow check
            if (b > 0 && a < LL_MIN + b) throw std::overflow_error("Subtraction underflow");
            return a - b;
        case '*':
            // Handle cases with 0 and 1 to prevent division by zero in the check
            if (b == 0 || a == 0) return 0;
            if (b == 1) return a;
            if (a == 1) return b;
            // Overflow check: if a is greater than MAX / b, then a * b will be > MAX.
            if (a > LL_MAX / b) throw std::overflow_error("Multiplication overflow");
            // Underflow check
            if (a < LL_MIN / b) throw std::overflow_error("Multiplication underflow");
            return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
    }
    return 0;
}

// The evaluate function now uses 'number_t' (long long)
number_t evaluate(std::string expression) {
    std::stack<number_t> values;
    std::stack<char> ops;

    for (int i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) {
            continue; // Skip whitespace
        }
        else if (isdigit(expression[i])) {
            number_t val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                number_t val2 = values.top();
                values.pop();
                number_t val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        number_t val2 = values.top();
        values.pop();
        number_t val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

    void generateAllExpressions(string& num, int index, string current_path, vector<string>& results) {
        // Base Case: If we have used all the digits from the input 'num' string
        if (index == num.length()) {
            // We have a complete expression, so add it to our list.
            results.push_back(current_path);
            return;
        }

        // Loop to form the next number. It can be 1 digit, 2 digits, etc.
        for (int i = index; i < num.length(); ++i) {
            // The next number we are considering
            string next_operand_str = num.substr(index, i - index + 1);

            // *** THE CRITICAL LEADING ZERO CHECK ***
            // If the number we just formed has more than one digit AND it starts with '0',
            // then it is an invalid number (like "05", "019"). We must stop.
            if (next_operand_str.length() > 1 && next_operand_str[0] == '0') {
                break; // Stop extending this number, as it's invalid.
            }
            
            // If this is the very first number we are adding to the path...
            if (index == 0) {
                // ...just add it without any operator.
                generateAllExpressions(num, i + 1, next_operand_str, results);
            } else {
                // Otherwise, add the number with each possible operator.
                generateAllExpressions(num, i + 1, current_path + "+" + next_operand_str, results);
                generateAllExpressions(num, i + 1, current_path + "-" + next_operand_str, results);
                generateAllExpressions(num, i + 1, current_path + "*" + next_operand_str, results);
            }
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> res;
        int n=num.size();
        int idx=0;
        string curr="";
        generateAllExpressions(num,idx,curr,res);
        vector<string> ans;
        for(auto& ele:res){
            if(evaluate(ele)==target) ans.push_back(ele);
        }
        return ans;
    }
};


// kind of TLE solution 
// will try it after some fays again