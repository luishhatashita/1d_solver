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
