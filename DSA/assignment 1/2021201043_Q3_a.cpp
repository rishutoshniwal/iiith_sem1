

#include <iostream>

using namespace std;

template<class T> void transpose(T *a, int r,int c)
{
        
        int nz[c],index[c+1];
         int count=0;
           for (int j=0;j<c;j++){
               nz[j]=0;
               for (int i = 0; i <r; i ++){
               if(*(a+i*c+j) !=0){
               nz[j]+=1;
               count++;
               }
              
           }
        }
        
        index[0]=1;
        for(int i=1;i<=c;i++){
        index[i]=index[i-1]+nz[i-1];
        // cout<<index[i]<<" ";
        
        }
        //  cout<<"\n";
        // for(int i=0;i<c;i++)
        // cout<<nz[i]<<" ";
        // cout<<"\n";
        
        
         T triplet[count+1][3];
         triplet[0][0]=r;
         triplet[0][1]=c;
         triplet[0][2]=count;
         
        int mark=1;
        
        for (int j=0;j<c;j++){
             for (int i=0; i<r;i++){
                  if(*(a+i*c+j) !=0){
                      triplet[mark][0]=j;
                      triplet[mark][1]=i;
                      triplet[mark][2]=*(a+i*c+j);
                      mark++;
                  }
                 
             }
        }
        
        
        T trans[count+1][3];
        for(int i=1;i<=count;i++)
        {
            int val=index[triplet[i][0]];
            trans[val][0]=triplet[i][0];
            trans[index[triplet[i][0]]][1]=triplet[i][1];
            trans[index[triplet[i][0]]][2]=triplet[i][2];
            index[triplet[i][0]]++;
        }
        
        trans[0][0]=c;
        trans[0][1]=r;
        trans[0][2]=count;
        
        
        for(int i=1;i<=count;i++)
        {
            
            cout<<trans[i][0]<<" "<<trans[i][1]<<" "<<trans[i][2]<<"\n";
        }
  
}


template<class T> void addition(T *a, int r1,int c1,T *b, int r2,int c2)
{
        if(r1!=r2 || c1!=c2){
           
        return;
        }
        
         int count1=0,count2=0,both=0;
        for (int i=0;i<r1;i++){
            for (int j=0;j<c1;j++){
                 if(*(a+i*c1+j) !=0)
                 count1++;
                 if(*(b+i*c1+j) !=0)
                 count2++;
                 if(*(a+i*c1+j) !=0 && *(b+i*c1+j) !=0)
                 both++;
                 
            }
        }
        
         T triplet1[count1][3],triplet2[count2][3];
         int mark1=0,mark2=0;
         for (int i=0;i<r1;i++){
            for (int j=0;j<c1;j++){
                
                 if(*(a+i*c1+j) !=0){
                     triplet1[mark1][0]=i;
                      triplet1[mark1][1]=j;
                      triplet1[mark1][2]=*(a+i*c1+j);
                      mark1++;
                 
                 }
                 
                 
                 if(*(b+i*c1+j) !=0){
                     triplet2[mark2][0]=i;
                      triplet2[mark2][1]=j;
                      triplet2[mark2][2]=*(b+i*c1+j);
                      mark2++;
                
                 }
                 
            }
        }
        
        T sum[count1+count2-both][3];
        int insert=0;
        mark1=0,mark2=0;
        while(mark1<count1 && mark2<count2)
        {
            if(triplet1[mark1][0]==triplet2[mark2][0])
            {
                if(triplet1[mark1][1]==triplet2[mark2][1])
                {
                    sum[insert][0]=triplet1[mark1][0];
                    sum[insert][1]=triplet1[mark1][1];
                    sum[insert][2]=triplet1[mark1][2]+triplet2[mark2][2];
                    mark1++;
                    mark2++;
                    insert++;
                    
                }
                else if(triplet1[mark1][1]<triplet2[mark2][1]){
                     sum[insert][0]=triplet1[mark1][0];
                    sum[insert][1]=triplet1[mark1][1];
                    sum[insert][2]=triplet1[mark1][2];
                    mark1++;
                    insert++;
                    
                }
                else{
                     sum[insert][0]=triplet2[mark2][0];
                    sum[insert][1]=triplet2[mark2][1];
                    sum[insert][2]=triplet2[mark2][2];
                    mark2++;
                    insert++;
                }
            }
            
            
            else if(triplet1[mark1][0]<triplet2[mark2][0]){
                sum[insert][0]=triplet1[mark1][0];
                    sum[insert][1]=triplet1[mark1][1];
                    sum[insert][2]=triplet1[mark1][2];
                    mark1++;
                    insert++;
                
            }
            else{
                  sum[insert][0]=triplet2[mark2][0];
                    sum[insert][1]=triplet2[mark2][1];
                    sum[insert][2]=triplet2[mark2][2];
                    mark2++;
                    insert++;
            }
        }
        
        
        while(mark1<count1){
              sum[insert][0]=triplet1[mark1][0];
                    sum[insert][1]=triplet1[mark1][1];
                    sum[insert][2]=triplet1[mark1][2];
                    mark1++;
                    insert++;
        }
        
        
        while(mark2<count2){
            sum[insert][0]=triplet2[mark2][0];
                    sum[insert][1]=triplet2[mark2][1];
                    sum[insert][2]=triplet2[mark2][2];
                    mark2++;
                    insert++;
        }
        
        
        
        
        // cout<<count1<<"\n";
        // cout<<count2<<"\n";
        // cout<<both<<"\n";
        for(int i=0;i<count1+count2-both;i++)
        {
            
            cout<<sum[i][0]<<" "<<sum[i][1]<<" "<<sum[i][2]<<"\n";
        }
          
  
}


template<class T> void multiplication(T *a, int r1,int c1,T *b, int r2,int c2){
    if(c1!=r2)
    return;
    
     int count1=0;
     for (int i=0;i<r1;i++){
            for (int j=0;j<c1;j++){
                 if(*(a+i*c1+j) !=0)
                 count1++;
            }
     }
     
     
      T triplet1[count1][3];
      int mark1=0;
     for (int i=0;i<r1;i++){
            for (int j=0;j<c1;j++){
                
                 if(*(a+i*c1+j) !=0){
                     triplet1[mark1][0]=i;
                      triplet1[mark1][1]=j;
                      triplet1[mark1][2]=*(a+i*c1+j);
                      mark1++;
                 
                 }
            }
     }
     
     
     int count2=0;
     for (int i=0;i<r2;i++){
            for (int j=0;j<c2;j++){
                 if(*(b+i*c2+j) !=0)
                 count2++;
            }
     }
     
     
     T triplet2[count2][3];
      int mark2=0;
       for (int j=0;j<c2;j++){
             for (int i=0; i<r2;i++){
                 if(*(b+i*c2+j) !=0){
                     triplet2[mark2][0]=j;
                      triplet2[mark2][1]=i;
                      triplet2[mark2][2]=*(b+i*c2+j);
                      mark2++;
                 }
             }
       }
       
       
    //     for(int i=0;i<count1;i++)
    //       cout<<triplet1[i][0]<<" "<<triplet1[i][1]<<" "<<triplet1[i][2]<<"\n";
    //       cout<<"sardar khan \n";
       
    //   for(int i=0;i<count2;i++)
    //       cout<<triplet2[i][0]<<" "<<triplet2[i][1]<<" "<<triplet2[i][2]<<"\n";
    //       cout<<"sardar khan \n";
       
       
       T prod[count1*count2][3];
       for(int i=0;i<count1*count2;i++)
       {
           prod[i][0]=-1;
           prod[i][1]=-1;
           prod[i][2]=-1;
       }
       
       
       int insert=0;
       for(int i=0;i<count1;i++)
       {
           for(int j=0;j<count2;j++)
           {
               if(triplet1[i][1]==triplet2[j][1])
               {
                   prod[insert][0]=triplet1[i][0];
                   prod[insert][1]=triplet2[j][0];
                   prod[insert][2]=triplet1[i][2]*triplet2[j][2];
                   insert++;
               }
           }
       }
       
       
    //   for(int i=0;i<insert;i++){
    //       if(prod[i][0]!=-1 && prod[i][1]!=-1)
    //       cout<<prod[i][0]<<" "<<prod[i][1]<<" "<<prod[i][2]<<"\n";
           
    //   }
    //   cout<<"faizal \n";
       
       for(int i=0;i<insert;i++)
       {
           for(int j=i+1;j<insert;j++)
           {
               if(prod[i][0]==prod[j][0] && prod[i][1]==prod[j][1])
               {
                   prod[i][2]=prod[i][2]+prod[j][2];
                   prod[j][0]=-1;
                   prod[j][1]=-1;
                   prod[j][2]=-1;
                   
               }
           }
       }
       
       
      for(int i=0;i<insert-1;i++)
      {
          for(int j=0;j<insert-i-1;j++)
          {
              if((prod[j][0]>prod[j+1][0]) || (prod[j][0]==prod[j+1][0] && prod[j][1]>prod[j+1][1])   )
              {
                  T temp=prod[j][0];
                  prod[j][0]=prod[j+1][0];
                  prod[j+1][0]=temp;
                   
                  temp=prod[j][1];
                  prod[j][1]=prod[j+1][1];
                  prod[j+1][1]=temp;
                   
                   
                  temp=prod[j][2];
                  prod[j][2]=prod[j+1][2];
                  prod[j+1][2]=temp;
                   
              }
          }
      }
       
       
       for(int i=0;i<insert;i++){
           if(prod[i][0]!=-1 && prod[i][1]!=-1)
           cout<<prod[i][0]<<" "<<prod[i][1]<<" "<<prod[i][2]<<"\n";
           
       }
     
     
      
    
}




int main()
{
    // int arr1[3][3] =
    // {
    //   {0,0,1},
    //   {2,1,0},
    //   {0,4,3}
    // };
    
    
    // // transpose(*arr1,3,4);
    //  int arr2[3][3] =
    // {
       
    //   {0,0,7},
    //   {6,3,0},
    //   {5,0,0}
    // };
    // // cout<<"rishu\n";
    // multiplication(*arr1,3,3,*arr2,3,3);
    // return 0;
}
