
    1.Crear un arreglo con para procesar 
    2.Para cada elemento inicialicar 1 l y en q+1 r;
    for(int i=1;i<=n;i++){
        m[i].x=1,m[i].y=q+1;
    }
    bool flag=true;
    while(flag){
        flag=false;
        // limpiar la estructura de datos
        for(int i=0;i<=4*n+5;i++)st[i]=0,lazy[i]=0;
        for(int i=1;i<=n;i++)
           //Si es diefente l!=r se procesa;
          if(m[i].x!=m[i].y){ flag=true;tocheck[(m[i].x+m[i].y)/2].push_back(i);}
        for(int i=1;i<=q;i++){
            if(!flag)break;
            // Se aplican las queries
            update(0,n-1,qs[i].x,qs[i].y,qs[i].z,0);
            update(0,n-1,qs[i].x,qs[i].x,qs[i].k,0);
            while(tocheck[i].size()){
                int id=tocheck[i].back();
                tocheck[i].pop_back();
                // Se obserba si se cumblio la caondicion para el elemeto
                if(ai[id]<=query(0,n-1,S[id],S[id],0)) m[id].y=i;
                else m[id].x=i+1;
            }
        }
    }
    // Solo se imprime
    for(int i=1;i<=n;i++){
        if(m[i].x<=q) cout<<m[i].x<<endl;
        else cout<<-1<<endl;
    }