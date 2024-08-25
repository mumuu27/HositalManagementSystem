#include<bits/stdc++.h>
#include<string.h>
using namespace std;
int patNum=0;
int deletedpat=0;
void RelativesToVisit();
int j=0;

int priorityy(char symm)
{
    switch(symm)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default :
        return 0;
    }
}

class ST_OT
{
public:
    int TopOT;
    ST_OT()
    {
        TopOT=-1;
    }
    char opErator[100];
    void Push(char);
    char Pop();
    char Top();
    bool isEmpty();
};

void ST_OT::Push(char ch)
{
    TopOT++;
    opErator[TopOT]=ch;
}

bool ST_OT::isEmpty()
{
    if(TopOT==-1)
        return true;
    else
        return false;
}

char ST_OT::Pop()
{
    return opErator[TopOT--];
}

char ST_OT::Top()
{
    return opErator[TopOT];
}

class ST_OP
{
public:
    int digit[100];
    int TopOp;
    ST_OP()
    {
        TopOp=-1;
    }
    void Push(int);
    int Pop();
    int Top();
    bool isEmpty();
};

void ST_OP::Push(int innt)
{
    TopOp++;
    digit[TopOp]=innt;
}

bool ST_OP::isEmpty()
{
    if(TopOp==-1)
        return true;
    else
        return false;
}

int ST_OP::Pop()
{
    return digit[TopOp--];
}

int ST_OP::Top()
{
    return digit[TopOp];
}

class PosfixEvaluation
{
public:

    string ReceivePostfix(string);
    int EvaluatePostfix(string expression);
    int PerformOperation(char operation, int operand1, int operand2);
    bool IsOperator(char C);
    bool IsNumericDigit(char C);
};

class InfixToPostfixTranslate
{
public:
    string PostFix;
    InfixToPostfixTranslate()
    {
        PostFix = "";
    }
    string getString(string);
    bool IsNumeric(char);
    void symboll(char,ST_OT &);
};

string InfixToPostfixTranslate::getString(string infixx)
{
    ST_OP operaand;
    ST_OT oper;
    int len=infixx.length();
    for(int i=0; i<len; i++)
    {
        if(IsNumeric(infixx[i]))
        {
            int operand = 0;
            while(i<len && IsNumeric(infixx[i]))
            {
                operand = (operand*10) + (infixx[i] - '0');
                i++;
            }
            i--;
            std::string strOp="";
            strOp =std::to_string(operand);
            PostFix +=strOp+' ';
        }
        else
        {
            symboll(infixx[i],oper);
        }
    }
    while (!oper.isEmpty())
    {
        PostFix += oper.Pop();
        PostFix +=' ';
    }
    return PostFix;
}

bool InfixToPostfixTranslate::IsNumeric(char ch)
{
    if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
    {
        return true;
    }
    else
        return false;
}

void InfixToPostfixTranslate::symboll(char sym, ST_OT &oper)
{
    if (sym == '(')
    {
        oper.Push(sym);
    }
    else if (sym == ')')
    {
        while (!oper.isEmpty() && oper.Top() != '(')
        {
            PostFix += oper.Pop();
            PostFix +=' ';
        }
        if (!oper.isEmpty() && oper.Top() == '(')
        {
            oper.Pop();
        }
    }
    else
    {
        while (!oper.isEmpty() && priorityy(sym) <= priorityy(oper.Top()))
        {
            PostFix += oper.Pop();
            PostFix +=' ';
        }
        oper.Push(sym);
    }
}

int PosfixEvaluation::EvaluatePostfix(string expression)
{
    ST_OP S;
    for(int i = 0; i< expression.length(); i++)
    {
        if(expression[i] == ' ' || expression[i] == ',') continue;
        else if(IsOperator(expression[i]))
        {
            int operand2 = S.Top();
            S.Pop();
            int operand1 = S.Top();
            S.Pop();
            int result = PerformOperation(expression[i], operand1, operand2);
            S.Push(result);
        }
        else if(IsNumericDigit(expression[i]))
        {
            int operand = 0;
            while(i<expression.length() && IsNumericDigit(expression[i]))
            {
                operand = (operand*10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.Push(operand);
        }
    }
    return S.Top();
}

bool PosfixEvaluation::IsNumericDigit(char C)
{
    if(C >= '0' && C <= '9') return true;
    return false;
}

bool PosfixEvaluation :: IsOperator(char C)
{
    if(C == '+' || C == '-' || C == '*' || C == '/'|| C == '^')
        return true;

    return false;
}

int PosfixEvaluation:: PerformOperation(char operation, int operand1, int operand2)
{
    if(operation == '+') return operand1 +operand2;
    else if(operation == '-') return operand1 - operand2;
    else if(operation == '*') return operand1 * operand2;
    else if(operation == '/') return operand1 / operand2;
    else if(operation == '^') return operand1 ^ operand2;
    else cout<<"Unexpected Error \n";
    return -1;
}

class Patient
{
public:
    string P_name;
    string p_case;
    string P_date_of_admit;
    int P_room;
    int P_regNo;
    Patient* nexLink;
    Patient* prevLink;
    Patient()
    {
        P_name="";
        p_case="";
        P_date_of_admit="";
        P_room=0;
        P_regNo=0;
        nexLink=NULL;
        prevLink=NULL;
    }
    Patient(string name,string Case,string date,int room,int registrationNo)
    {
        P_name=name;
        p_case=Case;
        P_date_of_admit=date;
        P_room=room;
        P_regNo=registrationNo;
        nexLink=NULL;
        prevLink=NULL;
    }
    void PrintInfo()
    {
        cout<<"Name of the patient "<<P_name<<endl;
        cout<<"Case of the patient "<<p_case<<endl;
        cout<<"Date of admission of the patient "<<P_date_of_admit<<endl;
        cout<<"Room assigned to "<<P_room<<endl;
        cout<<"Registration no. of the patient "<<P_regNo<<endl;
        cout<<endl;
    }
};

class Register
{
public:
    Patient* firstPatient;
    Register()
    {
        firstPatient=NULL;
    }
    Patient* arrayOfPatient[100];
    string arrayOfcheckedoutPatient[100];
    void storedInTheArray();
    void enterInfo();
    void EnterInTheReg(string,string,string,int,int);
    bool PreviouslyAdmitted(string);
    void PrintTheReg();
    int emptyyy();
    void searchW_R_T_reg(int);
    void searchW_R_T_Name(string);
    void searchW_R_T_date(string);
    void whoIsIt();
    void sort_w_r_t_reg();
    void sort_w_r_t_room();
    void DELETE_patient_W_R_T_Reg(int);
    int bill(string);
};

int Register::bill(string CASEE)
{
    int day=rand()%(10-1+1)+1;
    cout<<"You've stayed "<<day<<"days."<<endl;
    int perday=5000;
    cout<<"Per day cost is "<<perday<<endl;
    std::string DayStr=std::to_string(day);
    int MRI=10000;
    int Chemotherapy=50000;
    int BloodTest=500;
    int Ultrasonography=5000;
    int Oxygen = 300;
    int X_ray=500;
    int ECG=6000;
    int ETT=5000;
    if(CASEE=="Cancer")
    {
        cout<<"Chemotherapy = "<<Chemotherapy<<"/-"<<endl;
        string COST="5000*"+DayStr+"+50000 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost = "<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }

    else if(CASEE=="Heart Disease")
    {
        cout<<"ECG = "<<ECG<<"/-"<<endl;
        cout<<"ETT = "<<ETT<<"/-"<<endl;
        string COST="5000*"+DayStr+"+6000+5000 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else if(CASEE=="Asthma")
    {
        cout<<"Oxygen = "<<Oxygen<<"/-"<<endl;
        string COST="5000*"+DayStr+"+300 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else if(CASEE=="Ulcer")
    {
        cout<<"Ultrasonography = "<<Ultrasonography<<"/-"<<endl;
        string COST="5000*"+DayStr+"+5000 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else if(CASEE=="Pneumonia")
    {
        cout<<"Oxygen = "<<Oxygen<<"/-"<<endl;
        string COST="5000*"+DayStr+"+300 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost ="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else if(CASEE=="Dengue")
    {
        cout<<"BloodTest = "<<BloodTest<<"/-"<<endl;
        string COST="5000*"+DayStr+"+500 ";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost ="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else if(CASEE=="Accident")
    {
        cout<<"X_ray = "<<X_ray<<"/-"<<endl;
        cout<<"MRI = "<<MRI<<"/-"<<endl;
        string COST="5000*"+DayStr+"+500+10000";
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost ="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
    else
    {
        string COST="5000*"+DayStr;
        cout<<COST<<endl;
        InfixToPostfixTranslate inftoPost;
        string POSTFIX;
        POSTFIX=inftoPost.getString(COST);
        PosfixEvaluation COSTT;
        int BILL=COSTT.EvaluatePostfix(POSTFIX);
        cout<<"Total Cost ="<<COSTT.EvaluatePostfix(POSTFIX)<<endl;
        return BILL;
    }
}

void Register::storedInTheArray()
{
    Patient* Patients;
    cout<<"List of case in the register :"<<endl;
    for(int i=0; i<patNum; i++)
    {
        cout<<"case"<<i+1<<endl;
        Patients=arrayOfPatient[i];
        Patients->PrintInfo();
    }
}

void Register::sort_w_r_t_reg()
{
    int ptr;
    Patient* temp;
    for(int k=1; k<patNum; k++)
    {
        temp=arrayOfPatient[k];
        ptr=k-1;
        while((temp->P_regNo)<(arrayOfPatient[ptr]->P_regNo)&&(ptr>=0))
        {
            arrayOfPatient[ptr+1]=arrayOfPatient[ptr];
            ptr=ptr-1;
        }
        arrayOfPatient[ptr+1]=temp;
    }
    cout<<"Sorted Register with respect to Registration number "<<endl;
    cout<<"_________________________________________________________________________________________"<<endl;
    storedInTheArray();
    cout<<"_________________________________________________________________________________________"<<endl;
    cout<<endl;
}

void Register::sort_w_r_t_room()
{
    int ptr;
    Patient* temp;
    for(int k=1; k<patNum; k++)
    {
        temp=arrayOfPatient[k];
        ptr=k-1;
        while((temp->P_room)<(arrayOfPatient[ptr]->P_room)&&(ptr>=0))
        {
            arrayOfPatient[ptr+1]=arrayOfPatient[ptr];
            ptr=ptr-1;
        }
        arrayOfPatient[ptr+1]=temp;
    }
    cout<<"Sorted Register with respect to Room number "<<endl;
    cout<<"_________________________________________________________________________________________"<<endl;
    storedInTheArray();
    cout<<endl;
    cout<<"_________________________________________________________________________________________"<<endl;
}

int Register::emptyyy()
{
    if(firstPatient==NULL)
    {
        return 1;
    }
    else
        return 0;
}

void Register::enterInfo()
{
    string name;
    string cAse;
    string date_of_admit;
    cin.ignore();
    cout<<"Enter name : "<<endl;
    getline(cin,name);
    cout<<"Enter case : "<<endl;
    getline(cin,cAse);
    cout<<"Enter Today's date : "<<endl;
    getline(cin,date_of_admit);
    int L_room,U_room;
    int registerInTheRoom=rand()%(150-100+1)+100;
    int L_regNo,U_regNo;
    int registrationNo=rand()%(189000-181001+1)+181001;
    if(PreviouslyAdmitted(name))
    {
        cout<<"Looks like you were previously admitted Sir/ Ma'am. In such cases we actually give our patients some DISCOUNT "<<endl;
        EnterInTheReg(name,cAse,date_of_admit,registerInTheRoom,registrationNo);
    }
    else
    {
        EnterInTheReg(name,cAse,date_of_admit,registerInTheRoom,registrationNo);
    }
}

void Register::EnterInTheReg(string namee,string casee,string datee,int rooom,int regg)
{
    Patient* newPatient=new Patient(namee,casee,datee,rooom,regg);
    Patient* temp=firstPatient;
    if(firstPatient==NULL)
    {
        firstPatient=newPatient;
    }
    else
    {
        while(temp->nexLink!=NULL)
        {
            temp=temp->nexLink;
        }
        temp->nexLink=newPatient;
        newPatient->prevLink=temp;
    }
    cout<<endl;
    cout<<"The Receptionist : Here's a soft copy of the patient's Information and given Registration no. and Room no.:"<<endl;
    cout<<"___________________________________________________________________________________________________________________"<<endl;
    newPatient->PrintInfo();
    cout<<"___________________________________________________________________________________________________________________"<<endl;
    cout<<"Please, keep it for future procedure. Thank you."<<endl;
    cout<<endl;
    arrayOfPatient[patNum]=newPatient;
    patNum++;
}

void Register::PrintTheReg()
{
    Patient* temp=firstPatient;
    if(firstPatient==NULL)
    {
        cout<<"No patient yet. "<<endl;
    }
    else
    {
        while(temp!=NULL)
        {
            temp->PrintInfo();
            temp=temp->nexLink;
        }
    }
}

bool Register::PreviouslyAdmitted(string patNaamee)
{
    for(int i=0; i<=deletedpat; i++)
    {
        if(arrayOfcheckedoutPatient[i]==patNaamee)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Register::searchW_R_T_reg(int rEg)
{
    Patient* temppoo=firstPatient;
    while(temppoo->P_regNo!=rEg)
    {
        temppoo=temppoo->nexLink;
    }
    temppoo->PrintInfo();
}

void Register::searchW_R_T_Name(string namm)
{
    Patient* temppoo=firstPatient;
    while(temppoo->P_name!=namm)
    {
        temppoo=temppoo->nexLink;
    }
    temppoo->PrintInfo();
}

void Register::searchW_R_T_date(string Datee)
{
    Patient* temppoo=firstPatient;
    while(temppoo!=NULL)
    {
        if(Datee == temppoo->P_date_of_admit)
        {
            temppoo->PrintInfo();
        }
        temppoo=temppoo->nexLink;
    }
}

void Register::DELETE_patient_W_R_T_Reg(int regg)
{
    Patient* temp=firstPatient;
    if(temp->P_regNo==regg)
    {

        arrayOfcheckedoutPatient[deletedpat]=temp->P_name;
        deletedpat++;
        patNum--;
        delete temp;
    }
    else
    {
        while(temp->nexLink->P_regNo!=regg)
        {
            temp=temp->nexLink;
        }
        Patient* todel=temp->nexLink;
        temp->nexLink=todel->nexLink;
        todel->prevLink=temp;
        arrayOfcheckedoutPatient[deletedpat]=todel->P_name;
        deletedpat++;
        patNum--;
        delete todel;
    }
}

void Register::whoIsIt()
{
    cout<<"How can I help you Sir/Ma'am \nAre you here for \n1.Admiting a patient.\n2.Visiting someone.\n3.Checking out \n4.Duty(I'm a Doctor) "<<endl;
    int options;
    cout<<endl;
    cout<<"User : ";
    cin>>options;
    cout<<endl;
    if(options==1)
    {
        enterInfo();
    }
    else if(options==2)
    {
        if(emptyyy()==1)
        {
            cout<<"Sorry, there is no patient admitted at this moment. Please search in another hospital";
        }
        else
        {
            cout<<"Okay. So, Whom do you want to visit? Can you tell me his/her registration number. \n1)yes\n2)no"<<endl;
            int optionss;
            int regNOO;
            cin>>optionss;
            if(optionss==1)
            {
                cout<<"Okay. Then please tell me the Registration Number"<<endl;
                cin>>regNOO;
                cout<<"Please. let me check."<<endl;
                searchW_R_T_reg(regNOO);
            }
            else
            {
                cout<<"Can you tell me his/ her name ?\n(1)Yes\n(2)No"<<endl;
                int opp;
                cin>>opp;
                cout<<endl;
                if(opp==1)
                {
                    cout<<"Please tell me then "<<endl;
                    string naaaameee;
                    cin.ignore();
                    getline(cin,naaaameee);
                    searchW_R_T_Name(naaaameee);
                }
                else
                {
                    cout<<"Okay. Then Please me the date the patient had entered - ";
                    string dateee;
                    cin.ignore();
                    getline(cin,dateee);
                    cout<<"Here is the list of patient those had been admitted "<<dateee<<" day"<<endl;
                    searchW_R_T_date(dateee);
                }
            }
        }
    }
    else if(options==3)
    {
        cout<<"Enter the registration number of the patient for check out please : ";
        int reggg;
        cin>>reggg;
        cout<<"Here's your bill "<<endl;
        cout<<"___________________________________________________________________________________________________________________"<<endl;
        Patient* temppoo=firstPatient;
        while(temppoo->P_regNo!=reggg)
        {
            temppoo=temppoo->nexLink;
        }
        if(PreviouslyAdmitted(temppoo->P_name))
        {
            int BiLL=bill(temppoo->p_case);
            cout<<"But with discount, you have to pay "<<0.3*BiLL<<"/-"<<endl;
        }
        else
        {
            bill(temppoo->p_case);
        }
        DELETE_patient_W_R_T_Reg(reggg);
        cout<<"Check out completed"<<endl;
        cout<<"___________________________________________________________________________________________________________________"<<endl;
    }
    else if(options==4)
    {
        cout<<"Oh, hello Doctor! Seems like you're already in duty!\nHow would you like the patients list sorted - \n1)With respect to Room no.\n2)With respect to Registration No."<<endl;
        int optionnns;
        cin>>optionnns;
        if(optionnns==1)
        {
            cout<<"Here's the sorted list of patients with respect to Room No."<<endl;
            sort_w_r_t_room();
        }
        else
        {
            cout<<"Here's the sorted list of patients with respect to registration."<<endl;
            sort_w_r_t_reg();
        }
    }
}

int main()
{
    Register Pat;
    int InTheLine;
    cout<<"___________________________________________ HOSPITAL MANAGEMENT SYSTEM ____________________________________________"<<endl;
    cout<<"___________________________________________________________________________________________________________________"<<endl;
    cout<<endl;
    cout<<"The Receptionist : How many People is in the Waiting room? "<<endl;
    cout<<"The assistant : ";
    cin>>InTheLine;
    cout<<endl;
    for(int i=0; i<InTheLine; i++)
    {
        cout<<"The Receptionist : Number "<<i+1<<endl;
        cout<<"___________________________________________________________________________________________________________________"<<endl;
        cout<<endl;
        Pat.whoIsIt();
        cout<<"___________________________________________________________________________________________________________________"<<endl;
        cout<<"___________________________________________________________________________________________________________________"<<endl;
        cout<<endl;
        cout<<endl;
    }
    return 0;
}