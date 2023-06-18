
int fibonacci(int a, int b, int limit){

    if(b < a){
        b = a + b;
        printf(b);
        if(10000 < a + b)
            return b;
    }
    if(a+1<b){
        a = a + b;
        printf(a);
        if(10000 < a + b)
            return a;
    }

    return fibonacci(a, b, limit);
}

int main(){
    printf(0);
    printf(1);
    printf(1);

    printf(fibonacci(1,1,10000));
}