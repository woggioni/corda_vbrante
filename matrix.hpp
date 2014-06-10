#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;
typedef double val_t;
typedef short unsigned index_t;
typedef unsigned char bool_t;

struct range{
    index_t min;
    index_t max;
    range(index_t a, index_t b);
    };

class wvector{
    public:
        wvector(val_t start, val_t end, index_t length);
        wvector(index_t length, val_t value);
        wvector(index_t lenght);
        wvector();
        void randinit( index_t len, val_t min, val_t max);
        val_t* adress(void);
        void readr(val_t* adress, index_t len);
        void readr(val_t* adress);
        void clear();
        wvector clone();
        void print();
        void print(bool_t width);
        void set_from_str(index_t start, const char* string);
        void print_to_file(ofstream &tunnel, bool_t width);
        index_t len();
        val_t operator() (index_t pos);
        void operator() (index_t pos, val_t val);
        val_t operator * (wvector &v);
        val_t norm();
        //val_t max();
        //val_t min();
        val_t* a;
        index_t l;
    };

class matrix{
    public:
    void randinit(index_t,index_t, val_t, val_t);
    void set_from_str(index_t starting_row, index_t starting_column, const char* string);
    void fill_from_matrix(matrix m);
    val_t det(void);
    index_t rank();
    void print();
    void print(bool_t width);
    matrix (index_t,index_t,val_t);
    matrix (index_t,index_t);
    matrix ();
    void clear();
    void traspose();
    void traspose(matrix res);
    void eye(index_t dimension);
    matrix invert();
    int linsolve(matrix result, matrix column_myvector);
    int linsolve(wvector res, wvector sol);
    int get_column(wvector v,index_t column);
    int set_column(index_t column, wvector v);
    int set_row(index_t row, wvector v);
    matrix clone();
    matrix clone(range a, range b);
    val_t** operator& ();
    matrix operator* (matrix &a);
    wvector operator* (wvector a);
    val_t operator() (index_t row, index_t column);
    void operator() (index_t row, index_t column, val_t val);
    index_t size(bool_t);
    void matlab_print();
    void matlab_print(bool_t width);
    val_t** adress();
    val_t* adress(index_t row, index_t column);
    val_t** a;
    
    private:
    index_t gauss(void);
    index_t gauss(matrix lateral);
    index_t gauss_low(void);
    index_t gauss_low(matrix lateral);    
    void swap_rows(index_t r1, index_t r2);
    index_t r;
    index_t c;
    };

class timer{
public:
    timer(void);
    void reset(void);
    void stop(void);
    void tic(void);
    double get_time(void);
    void toc(void);
private:
    double tt[2];
    bool_t sw[2];
    };


int matprod(matrix p,matrix a, matrix b);
int mat_vec_prod(wvector p, matrix a, wvector v);
int vec_mat_prod(wvector p, wvector v, matrix a);
int vec_sum( wvector res, wvector v1, wvector v2);
range ft(const index_t a, const index_t b);
bool_t vec_scal_prod(wvector res, wvector v, val_t c);
