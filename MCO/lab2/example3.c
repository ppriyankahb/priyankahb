  int size=row*col;
    int temp[size];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            temp[i*col+j]=matrix[i][j];
        }
    }
    int temp2;
    for(int k=0;k<size;k++){
        for(int l=0;l<size-k-1;l++){
            if(temp[l]>temp[l+1])
            {
             temp2=temp[l];
             temp[l]=temp[l+1];
             temp[l+1]=temp2;
            }
        }
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=temp[i*col+j];
        }
    }

    printf("Sorted matrix is:\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
           printf("%d\t", matrix[i][j]);
           
        }
        printf("\n");
    }