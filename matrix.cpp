#include "matrix.hpp"

void timer::tic(){
    tt[0]=(double)clock();
    sw[0]=1;
    };

void timer::stop(){
    tt[1]=(double)clock();
    sw[1]=1;
    };

double timer::get_time(){
    if(sw[0]){
        if(sw[1])   return (tt[1]-tt[0])/CLOCKS_PER_SEC;
        else       return ((double)clock()-tt[0])/CLOCKS_PER_SEC;        
    }
    else cout<<"Clock not inizialized"<<endl;    
    return 0;
    };
    
void timer::toc(){
    if(sw[0]){
        if(sw[1])   cout << "Time elapsed is "<<(tt[1]-tt[0])/CLOCKS_PER_SEC << " seconds"<<endl;
        else       cout << "Time elapsed is "<<((double)clock()-tt[0])/CLOCKS_PER_SEC << " seconds"<<endl;        
    }
    else cout<<"Clock not inizialized"<<endl;    
};

void timer::reset(){
    for (bool_t i = 0; i < 2; i++)
    {
        tt[i]=0;
        sw[i]=0;
    }
};

wvector::wvector( index_t len, val_t val) {
    //a=(val_t*)malloc(sizeof(val_t)*l);
    l=len;
    a=new val_t [l];
    for (index_t i = 0; i < l; i++) a[i]=val;
    };

wvector::wvector(index_t len) {
    //a=(val_t*)malloc(sizeof(val_t)*l);
    l=len;
    a=new val_t [l];
    };

wvector::wvector(){};

void wvector::set_from_str(index_t start, const char* string){
index_t i=0,k=0;
const char * index;
while (string[i]!='\0'){
    while (string[i]!='\0' && (string[i]==' ' || string[i]=='\n' || string[i]=='\t' || string[i]==','))
        i++;
    index=&string[i];
    a[start+(k++)]=atof(index);
    while (string[i]!='\0' && string[i]!=' ' && string[i]!='\n' && string[i]!='\t' && string[i]!=',')
        i++;
    }
};

matrix::matrix(index_t r_input, index_t c_input, val_t val) {
r=r_input;
c=c_input;
//a=(val_t**)malloc(r*sizeof(val_t*));
a= new val_t* [r];
while(r_input--){
	//a[r_input]=(val_t*)malloc(c_input*sizeof(val_t));
    a[r_input]= new val_t [c_input];
	while(c_input--){
		a[r_input][c_input]=val;
	}
	c_input=c;
}
};

matrix::matrix(index_t r_input, index_t c_input) {
r=r_input;
c=c_input;
//a=(val_t**)malloc(r*sizeof(val_t*));n
a= new val_t* [r];
while(r_input--)
	//a[r_input]=(val_t*)malloc(c_input*sizeof(val_t));
    a[r_input]=new val_t [c_input];
};

matrix::matrix(){};

val_t matrix::operator () (index_t row, index_t column){
    return a[row-1][column-1];
    };

void matrix::operator () (index_t row, index_t column, val_t val){
    a[row-1][column-1]=val;
    };

void matrix::set_from_str(index_t st_r,index_t st_c, const char* string){
index_t i=0,k=0,j=0;
const char * index;
while (string[i]!='\0'){
    while (string[i]!='\0' && (string[i]==' ' || string[i]=='\n' || string[i]=='\t' || string[i]==','))
        i++;
    index=&string[i];
    //cout<< st_r+j<<'\t'<<st_c+k <<endl;
    a[st_r+j][st_c+k]=atof(index);
    k=(k+1)%c;
    if (k==0)
        j++;
    while (string[i]!='\0' && string[i]!=' ' && string[i]!='\n' && string[i]!='\t' && string[i]!=','){
        i++;
        if (string[i]==';' && k!=0){
            j++;
            k=0;
            }
        }
    }
};

void wvector::clear(){
    delete(a);
    };

wvector wvector::clone(){
    wvector copy(l,0);
    for (index_t i = 0; i < l; i++) copy.a[i]=a[i];    
    return copy;};

val_t wvector::norm(){
    val_t norm=0;
    for (index_t i = 0; i < l; i++) norm+=a[i]*a[i];
    norm=sqrt(norm);
    return norm;};

void wvector::print(){
    for (index_t i = 0; i < l; i++) cout << setw(4) << a[i]; //printf("%10.3e ", a[i]);
    printf("\n");
    };

void wvector::print(bool_t width){
    for (index_t i = 0; i < l; i++) cout << setw(width) << a[i]; //printf("%10.3e ", a[i]);
    printf("\n");
    };

void matrix::clear(){
    while(r>0)
        delete[] a[--r];
    delete[] a;
    //free(a);
    return;
    };

void matrix::randinit(index_t r_input , index_t c_input, val_t min, val_t max){
  r=r_input;
  c=c_input;
  //a=(val_t**)malloc(sizeof(val_t*)*r);
    a=new val_t* [r];
while(r_input--){
	//a[r_input]=(val_t*)malloc(sizeof(val_t)*c_input);
    a[r_input]=new val_t [c];
	while(c_input--){
		a[r_input][c_input]=min+(max-min)*rand()/RAND_MAX;
	}
	c_input=c;  
    }
};

void matrix::print(){
	int i,j;
	for (i=0;i<r;i++){
		for(j=0;j<c;j++)
            cout << setw(4) << a[i][j];
        //printf(" %1.3e",a[i][j]);
		puts("");
		}
    };

void matrix::print( bool_t width){
	int i,j;
	for (i=0;i<r;i++){
		for(j=0;j<c;j++)
            cout << setw(width) << a[i][j];
        //printf(" %1.3e",a[i][j]);
		puts("");
		}
    };

val_t matrix::det(void) {
    if(r!=c ) {
    printf("ERROR: IMPOSSIBLE TO CALCULATE DETERMINANT\n");
    return 0;
    }
    index_t accu;
	matrix m=clone();
	accu=m.gauss();	
    val_t det= accu%2 ? -1 : 1 ;
    for (index_t i=0;i<r;i++) det*=m.a[i][i];
    m.clear();
	return det;
    };

index_t matrix::rank(void) {
	index_t i,j,k;
	val_t f;
	matrix m;
    m=clone();
    m.gauss();
    j= r<c ? r-1 : c-1;
    for (i=0; i<r; i++)
	{
		if (i!=j && m.a[j][j])
		{
			f=m.a[i][j]/m.a[j][j];
			for (k=0; k<c; k++)
			{
				m.a[i][k]-=f*m.a[j][k];
			}
		}
	}
	m.print(10);
	cout << endl;
    index_t res=0;
    for (i=0;i<r;i++)
        for(j=0;j<c;j++)
            if(m.a[i][j]){
                res++;
                break;
            }		
	m.clear();
	return res;
}

index_t matrix::gauss(){
	index_t i,j,k;
	index_t accu=0;
	val_t f;
	for (i=0; i<r; i++)
	{
		k=r-1;
		while (a[i][i]==0 && k>i)
		{
			if ( a[k][i] ){
				swap_rows(i,k);
				accu++;
				}
			k--;
		}
		if ( a[i][i] )
			for (j=r-1; j>i; j--)
			{
			f=a[j][i]/a[i][i];
				for (k=0; k<c; k++)
				{
					a[j][k]-= f*a[i][k];
				}
			}	
	}
return accu;
}

index_t matrix::gauss(matrix lateral){
	if (lateral.r != r || lateral.c != c)
	{
		cout << "DIFFERENT LATERAL MATRIX DIMENSIONS:\nERROR IN GAUSS" << endl;
		return 0;
	}
	index_t i,j,k;
	index_t accu=0;
	val_t f;
	for (i=0; i<r; i++)
	{
		k=r-1;
		while (a[i][i]==0 && k>i)
		{
			if ( a[k][i] ){
				swap_rows(i,k);
				lateral.swap_rows(i,k);
				accu++;
				}
			k--;
		}
		if ( a[i][i] )
			for (j=r-1; j>i; j--)
			{
			f=a[j][i]/a[i][i];
				for (k=0; k<c; k++)
				{
					a[j][k]-= f*a[i][k];
					lateral.a[j][k]-= f*lateral.a[i][k];
				}
			}	
	}
return accu;
}

index_t matrix::gauss_low(){
	index_t i,j,k;
	index_t accu=0;
	val_t f;
	i=r;
	while (i-->0)
	{
		k=0;
		while (a[i][i]==0 && k<i)
		{
			if ( a[k][i] ){
				swap_rows(i,k);
				accu++;
				}
			k++;
		}
		if ( a[i][i] )
			for (j=0; j<i; j++)
			{
			f=a[j][i]/a[i][i];
				for (k=0; k<c; k++)
				{
					a[j][k]-= f*a[i][k];
				}
			}	
	}
return accu;
}

index_t matrix::gauss_low(matrix lateral){
	index_t i,j,k;
	index_t accu=0;
	val_t f;
	i=r;
	while (i-->0)
	{
		k=0;
		while (a[i][i]==0 && k<i)
		{
			if ( a[k][i] ){
				swap_rows(i,k);
				lateral.swap_rows(i,k);
				accu++;
				}
			k++;
		}
		if ( a[i][i] )
			for (j=0; j<i; j++)
			{
			f=a[j][i]/a[i][i];
				for (k=0; k<c; k++)
				{
					a[j][k]-= f*a[i][k];
					lateral.a[j][k]-= f*lateral.a[i][k];
				}
			}	
	}
return accu;
}

void matrix::traspose(){
	if (r!=c)
	{
		cout<< "MATRIX IS NOT SQUARE:\nERROR IN TRASPOSE\n";
		return;
	}
    index_t i,j;
    val_t temp;
    for (i=0;i<r;i++)
        for(j=0;j<i;j++){
			temp=a[j][i];
            a[j][i]=a[i][j];
            a[i][j]=temp;
            }
    return;
    };

void matrix::traspose(matrix res){
	if (res.size(1)!=c || res.size(2)!=r)
	{
		cout << "WRONG DESTINATION MATRIX DIMENSIONS:\nERROR IN TRASPOSE" << endl;
		return;
	} 
    index_t i,j;
    for (i=0;i<r;i++)
        for(j=0;j<c;j++){
            res.a[j][i]=a[i][j];
            }
    return;
    };

void matrix::eye(index_t d){
r=c=d;
//a=(val_t**)malloc(sizeof(val_t*)*d);
a= new val_t* [d];
for (index_t i = 0; i < d; i++){
	//a[i]=(val_t*)malloc(sizeof(val_t)*d);
    a[i]= new val_t [d];
	for (index_t j = 0; j < d; j++){        
        a[i][j]=(i==j);
	}
}
};


matrix matrix::invert(){
    matrix inv,m=clone();
    index_t i,j;
    inv.eye(r);
    if (r-c)
	{
		cout<<"IMPOSSIBLE TO INVERT A NON-SQUARE MATRIX\n";
        return m;
    }
    m.gauss(inv);
    m.gauss_low(inv);
    for (i=0; i<r; i++)
    {
		if (m.a[i][i])
			for(j=0; j<c; j++)
			{
				inv.a[i][j]/=m.a[i][i];
			}
		else
		{
			cout << "MATRIX IS SINGULAR OR BADLY SCALED:\nIMPOSSIBLE TO INVERT" << endl;
			return inv;
		}
	}
	m.clear();
	return inv;
	}



int matprod(matrix p, matrix a, matrix b){
int err=0;
if(a.size(2)!=b.size(1) || p.size(1)!=a.size(1) || p.size(2)!=b.size(2)){
		printf("Matrix dimension conflict\n");
		puts("ERROR: IMPOSSIBLE TO CALCULATE MATRIX PRODUCT");
		err=1;
	}
int i,j,k;
if (err) return -1;
for(i=1;i<=p.size(1);i++)
	for(j=1;j<=p.size(2);j++){
		p(i,j,0);
		for(k=1;k<=a.size(2);k++)
			p(i,j, p(i,j) + a(i,k) * b(k,j));
		}
return 0;}


int mat_vec_prod(wvector p, matrix a, wvector v){
    if (p.len()!=a.size(1) || v.len()!=a.size(2)){
            printf("Matrix dimension conflict\n");
            puts("ERROR: IMPOSSIBLE TO CALCULATE MATRIX PRODUCT");
            return -1;
        }
    index_t i,k;
    for(i=0;i<p.len();i++){
        p(i+1,0);
        for(k=0;k<a.size(2);k++)
            p( i+1, p(i+1) + a(i+1,k+1)*v(k+1) );
            }
    return 0;
    }
    
int vec_mat_prod(wvector p, wvector v, matrix a){
    if (p.len()!=a.size(2) || v.len()!=a.size(1)){
            printf("Matrix dimension conflict\n");
            puts("ERROR: IMPOSSIBLE TO CALCULATE MATRIX PRODUCT");
            return -1;
        }
    index_t i,k;
    for(i=0;i<p.len();i++){
        p(i+1,0);
        for(k=0;k<a.size(1);k++)
            p( i+1, p(i+1) + a(k+1,i+1)*v(k+1) );
            }
    return 0;
    }

val_t** matrix::operator & (){
    return a;
    };

wvector matrix::operator * (wvector v){
    wvector res(r,0);
    if (v.len()!=c){
            printf("Matrix dimension conflict\n");
            puts("ERROR: IMPOSSIBLE TO CALCULATE MATRIX-wvector PRODUCT");
            return res;
        }
    index_t i,k;
    for(i=0;i<r;i++){
        res(i+1,0);
        for(k=0;k<c;k++)
            res( i+1, res(i+1) + a[i][k]*v(k+1) );
            }
    return res;
    }

matrix matrix::operator * (matrix &mat){
int err=0;
if(mat.size(1)!=size(2)){
		printf("Matrix dimension conflict\n");
		puts("ERROR: IMPOSSIBLE TO CALCULATE MATRIX PRODUCT");
		err=1;
	}
index_t i,j,k;
matrix res(size(1),mat.size(2),0);
if (err) return res;
for(i=0;i<res.size(1);i++)
	for(j=0;j<res.size(2);j++){
		res(i+1,j+1,0);
		for(k=0;k<size(2);k++)
			res(i+1,j+1, res(i+1,j+1) + a[i][k] * mat(k+1,j+1));
		}    
return res;
    }

int matrix::linsolve(matrix res,matrix sol){
if (sol.r!=c || sol.c!=res.c || res.r!=c){
    cout << "Matrix dimension conflict: impossible to solve linear system\n";
    return -1;
    }
matrix inverse=invert();
matprod(res,inverse,sol);
inverse.clear();        
return 0;
}

int matrix::linsolve(wvector res, wvector sol){
if (sol.len()!=c || res.len()!=c){
    cout << "Matrix dimension conflict: impossible to solve linear system\n";
    return -1;
    }
mat_vec_prod(res,invert(),sol);        
return 0;
}

matrix matrix::clone(){
    matrix res(r,c,0);
    index_t i,j;
    for (i=0;i<r;i++)
        for (j=0;j<c;j++)
            res.a[i][j]=a[i][j];
    return res;
    }


matrix matrix::clone(range rows, range columns){
matrix res(rows.max-rows.min+1, columns.max-columns.min+1);
index_t i,j;
for (i=1; i<=res.size(1);i++)
    for (j=1; j<=res.size(2); j++)
        res(i,j, a[rows.min+i-2][j+columns.min-2]);
return res;
    };

index_t matrix::size(bool_t input){
    return (input-1 ? c : r);
    };

index_t wvector::len(){
    return l;
    };

val_t wvector::operator() (index_t pos){
return a[pos-1];
    };
    
void wvector::operator() (index_t pos, val_t val){
a[pos-1]=val;
    };

val_t wvector::operator * (wvector &v){
val_t res=0;
for (index_t i=0; i<l; i++)
    res += a[i]*v(i+1);
return res;
    };


void wvector::randinit(index_t l_input , val_t min, val_t max){
  l=l_input;
    a=new val_t [l];
while(l_input--){
    a[l_input] = min+(max-min)*rand()/RAND_MAX;
	}
};


void wvector::readr(val_t* adress, index_t len){
    l=len;
    a=adress;
    };

void wvector::readr(val_t* adress){
    a=adress;
    };

val_t* wvector::adress(void){
    return a;
    };

range::range(index_t a, index_t b){
if (b<a){
    min=b;
    b=a;
    a=min;
    }
min=a;
max=b;
}

range ft(const index_t a, const index_t b){
range res(a,b);
return res;
    }

void matrix::swap_rows(index_t r1, index_t r2){
    index_t i;
    val_t temp;
    for (i=0; i<c; i++)
        {
        temp=a[r1][i];
        a[r1][i]=a[r2][i];
        a[r2][i]=temp;
        }
}

int matrix::get_column(wvector v,index_t column){
	if (v.len()<r){
        cout << "DESTINATION wvector IS TOO SHORT\nERROR IN GET_COLUMN\n" << endl;
		return -1;
		}
	index_t i;
	for (i=0; i<r; i++){
		v(i+1,a[i][column-1]);
		}
	return 0;
}

int matrix::set_column(index_t column, wvector v){
	if (v.len()>r){
        cout << "DESTINATION wvector IS TOO LONG\nERROR IN SET_COLUMN\n" << endl;
		return -1;
		}
	index_t i;
	for (i=0; i<v.len(); i++){
		a[i][column-1]=v(i+1);
		}
	return 0;	
	}
	
int matrix::set_row(index_t row, wvector v){
	if (v.len()>c){
        cout << "DESTINATION wvector IS TOO LONG\nERROR IN SET_COLUMN\n" << endl;
		return -1;
		}
	index_t i;
	for (i=0; i<v.len(); i++){
		a[row-1][i]=v(i+1);
		}
	return 0;	
	}


void matrix::matlab_print(void){
	cout <<"\n[";
	index_t i,j;
	for (i = 0; i < r; i++)
	{
		for (j=0; j<c; j++)
			{
				cout << setw(4) <<  a[i][j];
			}
		cout <<';';
	}
	cout << ']' << endl;	
	}
	
void matrix::matlab_print(bool_t width){
	cout <<"\n[";
	index_t i,j;
	for (i = 0; i < r; i++)
	{
		for (j=0; j<c; j++)
			{
				cout << setw(width) <<  a[i][j];
			}
		cout <<';';
	}
	cout << ']' << endl;	
	}

void matrix::fill_from_matrix(matrix m){
	index_t mr, mc;
	mr=m.size(1);
	mc=m.size(2);
	if (mr>r || mc>c)
	{
		cout<< "ERROR IN fill_from_matrix:\nSOURCE IS TOO LARGE" << endl;
		return;
	}
	index_t i,j;
	for (i=1; i<=mr; i++)
	{
		for (j=1; j<=mc; j++)
		{
			a[i-1][j-1]=m(i,j);
		}
	}
return;
}

int vec_sum( wvector res, wvector v1, wvector v2)
{
	if( res.len() != v1.len() || v1.len() != v2.len() || res.len() != v2.len() )
	{
		cout << "ERROR IN vec_sum:\nmyvector LENGTH MISMATCH" << endl;
		return -1;
	}
	index_t i;
	for(i=1; i<= res.len(); i++)
	{
		res(i, v1(i)+v2(i));
	}
return 0;
}

val_t** matrix::adress()
{
	return a;
}

val_t* matrix::adress(index_t row, index_t column)
{
	return &a[row-1][column-1];
}

bool_t vec_scal_prod(wvector res, wvector v, val_t c)
{
	if (res.len() < v.len())
	{
        cout << "ERROR IN vec_scal_prod:\nDESTINATION wvector TOO SHORT" << endl;
		return 1;
	}
	index_t i;
	for(i=1; i <= v.len(); i++)
	{
		res(i, v(i)*c);
	}
	return 0;
}

wvector::wvector(val_t start, val_t end, index_t length)
{
	l=length;
	a= new val_t [l];
	index_t i;
	val_t step = (end-start)/(l-1);
	for (i=0; i<l; i++)
	{
		a[i]=start + i*step;
	}
	return;
}

void wvector::print_to_file(ofstream &tunnel, bool_t width)
{
	index_t i;
	for(i=0; i<l; i++)
	{
		tunnel << setw(width) << a[i];
	}
	tunnel<< "\n";
	return;
}
