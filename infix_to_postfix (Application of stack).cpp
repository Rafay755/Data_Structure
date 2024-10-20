#include <iostream>
#include <string>
#include <cctype>
using namespace std;

template <typename T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node() : next(nullptr) {}
    Node(T s) : data(s), next(nullptr) {}
    ~Node() {}
    template <typename U>
    friend class Stack;
};

template <typename T>
class Stack
{
    Node<T> *top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void push(T val)
    {
        Node<T> *newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T(); 
        }
        T val = top->data;
        Node<T> *temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    T Top() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return top->data;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

class VariableNode
{
public:
    string variableName;
    int value;
    VariableNode *next;

    VariableNode(string name, int val) : variableName(name), value(val), next(nullptr) {}
    VariableNode() : variableName(""), value(0), next(nullptr) {}
};

class Calculator
{
private:
    string infix;
    string postfix;
    char delimiter;

public:
    Calculator() : infix(""), postfix(""), delimiter(' ') {}

    void input()
    {
        cout << "Enter an infix expression: " << endl;
        getline(cin, infix);
    }

    bool isOperator(char op) const
    {
        return op == '/' || op == '*' || op == '+' || op == '-';
    }
    bool isAlpha(char ch)
    {
      
        return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
    }

    bool isDigit(char ch)
    {
      
        return (ch >= '0' && ch <= '9');
    }
    int precedence(char op) const
    {
        switch (op)
        {
        case '/':
        case '*':
            return 10;
        case '+':
        case '-':
            return 5;
        default:
            return -1;
        }
    }

    string infixToPostfix()
    {
        Stack<char> charStack;
        postfix.clear();
        int size = infix.size();
        for (size_t i = 0; i < size; ++i)
        {
            char ch = infix[i];
//while there are multiple num digit put it to postfix
            if (isdigit(ch))
            {
                while (i < infix.size() && isdigit(infix[i]))
                {
                    postfix += infix[i];
                    ++i;
                }
                postfix += delimiter;
                --i;
            }
            // push it to stack
            else if (ch == '(')
            {
                charStack.push(ch);
            }
            //pop untill you get )
            else if (ch == ')')
            {
                while (!charStack.isEmpty() && charStack.Top() != '(')
                {
                    postfix += charStack.pop();
                    postfix += delimiter;
                }
                if (!charStack.isEmpty() && charStack.Top() == '(')
                {
                    charStack.pop();
                }
            }
            //push to stack
            else if (isOperator(ch))
            {
                while (!charStack.isEmpty() && precedence(charStack.Top()) >= precedence(ch))
                {
                    postfix += charStack.pop();
                    postfix += delimiter;
                }
                charStack.push(ch);
            }
            else if (ch == ' ')
            {
                continue;
            }
            else if (isalpha(ch))
            {
                while (i < infix.size() && (isalnum(infix[i]) || infix[i] == '_'))
                {
                    postfix += infix[i];
                    ++i;
                }
                postfix += delimiter;
                --i;                 
            }
            else
            {
                cout << "Invalid character encountered: " << ch << endl;
                return "";
            }
        }

        while (!charStack.isEmpty())
        {
            postfix += charStack.pop();
            postfix += delimiter;
        }

        if (!postfix.empty() && postfix.back() == delimiter)
        {
            postfix.pop_back();
        }

        return postfix;
    }

    void displayInfix() const
    {
        cout << "Infix Expression: " << infix << endl;
    }

    void displayPostfix() const
    {
        cout << "Postfix Expression: " << postfix << endl;
    }

    double evaluatePostfix(const string &postfixExpression, VariableNode *head) const
    {
        Stack<double> s;
        string number;
        string variable;
        int size = postfix.size();
        for (size_t i = 0; i < size; ++i)
        {
            char ch = postfixExpression[i];
//it is not a var and it is a num
            if (isdigit(ch) && variable.empty())
            {
                number += ch;
            }
            // multiple num digit ends
            else if (ch == delimiter && !number.empty())
            {
                s.push(stod(number));
                number.clear();
            }
            //now you have to solve
            else if (isOperator(ch))
            {
                if (s.isEmpty())
                {
                    cout << "Error: Insufficient values in the expression." << endl;
                    return 0;
                }
                double right = s.pop();
                if (s.isEmpty())
                {
                    cout << "Error: Insufficient values in the expression." << endl;
                    return 0;
                }
                double left = s.pop();
                double result = solve(left, right, ch);
                s.push(result);
            }
            //it is a variable 
            else if (isalpha(ch) || (isdigit(ch) && !variable.empty()))
            {
                variable += ch;
            }
            else if (ch == delimiter && !variable.empty())
            {
                //check is it exist in record or postfix
                VariableNode *tracker = head;
                while (tracker != nullptr && tracker->variableName != variable)
                {
                    tracker = tracker->next;
                }
                if (tracker != nullptr)
                {
                    s.push(tracker->value);
                }
                else
                {
                    cout << "Variable not found: " << variable << endl;
                    return 0;
                }
                variable.clear();
            }
        }

        
        if (!number.empty())
        {
            s.push(stod(number));
        }

        if (s.isEmpty())
        {
            cout << "Error: No values to evaluate." << endl;
            return 0;
        }

        double result = s.Top();
        cout << "Result: " << result << endl;
        return result;
    }
//solve
    double solve(double L, double R, char op) const
    {
        switch (op)
        {
        case '/':
            return L / R;
        case '*':
            return L * R;
        case '-':
            return L - R;
        case '+':
            return L + R;
        default:
            return 0;
        }
    }

    string getInfix() const
    {
        return infix;
    }

    string getPostfix() const
    {
        return postfix;
    }
//get vars from input 
    VariableNode *extractVariables(const string &expression)
    {
        string temp;
        VariableNode *head = nullptr;
        VariableNode *tail = nullptr;
        int size = expression.size();
        for (size_t i = 0; i < size; ++i)
        {
            char ch = expression[i];

            if (isalpha(ch))
            {
                temp += ch;// add to var string
            }
            else if (isdigit(ch) && !temp.empty())
            {
                temp += ch;//it is a part of var name
            }
            else if (ch == delimiter || isOperator(ch) || ch == '(' || ch == ')')//var name ends
            {
                if (!temp.empty())
                {
                    cout << "Enter the value for variable " << temp << ": ";
                    int val;
                    cin >> val;
                    cin.ignore(); 

                    VariableNode *newNode = new VariableNode(temp, val);
                    if (head == nullptr)
                    {
                        head = newNode;
                        tail = newNode;
                    }
                    else
                    {
                        tail->next = newNode;
                        tail = newNode;
                    }
                    temp.clear();
                }
            }
        }

        // Process the last variable if any
        if (!temp.empty())
        {
            cout << "Enter the value for variable " << temp << ": ";
            int val;
            cin >> val;
            cin.ignore(); 

            VariableNode *newNode = new VariableNode(temp, val);
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }

        return head;
    }

    ~Calculator()
    {
       
    }
};

int main()
{
    Calculator calc;

    calc.input();

    int choice = 0;
    do
    {
        cout << "\n**************************************** Postfix to Infix Calculator ****************************************" << endl;
        cout << "Menu: " << endl;
        cout << "1. Display infix expression" << endl;
        cout << "2. Convert infix to postfix" << endl;
        cout << "3. Display postfix expression" << endl;
        cout << "4. Evaluate postfix expression" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            calc.displayInfix();
            break;

        case 2:
            calc.infixToPostfix();
            cout << "Infix expression converted to postfix." << endl;
            break;

        case 3:
            calc.displayPostfix();
            break;

        case 4:
        {
            VariableNode *variables = calc.extractVariables(calc.getInfix());
            double result = calc.evaluatePostfix(calc.getPostfix(), variables);
            cout << "Evaluation Result: " << result << endl;

            while (variables != nullptr)
            {
                VariableNode *temp = variables;
                variables = variables->next;
                delete temp;
            }
        }
        break;

        case 5:
            cout << "Exiting the program. Thank you for using the calculator!" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}