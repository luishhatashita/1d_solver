using namespace std;

class array1d
{
    private:
        int len;
        double *arr;
    public:
        array1d(int n);
        void printArray();
        ~array1d();
};

void printArray  (int n, double*& arr);
void arrayZeros  (int n, double*& arr);
void linSpace    (double xbegin, double xend, int n, double*& arr);
void spacingArray(int n, double*& arrin, double*& arrout);
void copyArray   (int n, double*& arrin, double*& arrout);
