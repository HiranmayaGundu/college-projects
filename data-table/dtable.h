struct table{
	int *data;
	int top;
	int size;
	double growth;
	double shrink;
};
typedef struct table table;
void insert(table *tab,int dat);
int pop(table *tab); 
