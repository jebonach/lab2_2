#include "ui.h"
#include <iostream>
#include <vector>

#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

#include "Queue.h"
#include "ArrayQueue.h"
#include "CycleQueue.h"
#include "ArrayPQueue.h"
#include "ListQueue.h"
#include "ListPQueue.h"

#include "errors.h"
#include "NewExceptions.h"

struct Item
{
    bool isSeq;
    Sequence<int>* seq;
    Queue<int>*    que;

    Item(Sequence<int>* s):isSeq(true), seq(s), que(nullptr){}
    Item(Queue<int>* q):isSeq(false),seq(nullptr), que(q){}
};

static void createObj (std::vector<Item>&);
static void appendObj (std::vector<Item>&);
static void printAll  (const std::vector<Item>&);
static void removeObj (std::vector<Item>&);

static void subseqObj (std::vector<Item>&);
static void concatObj (std::vector<Item>&);
static void removeItm (std::vector<Item>&);

static int  askID     (const std::vector<Item>&,const char* prompt);


void runUI()
{
    std::vector<Item> objs;
    bool run = true;

    while(run)
    {
        try{
            std::cout<<"\n=== MENU ===\n"
                     <<"1) Create sequence / queue\n"
                     <<"2) Append / Enqueue\n"
                     <<"3) Print ALL\n"
                     <<"4) Remove object\n"
                     <<"5) Subsequence (seq)\n"
                     <<"6) Concat      (seq)\n"
                     <<"7) Remove item / Dequeue\n"
                     <<"0) Exit\nChoose: ";

            int cmd; std::cin>>cmd;
            if(!std::cin){ std::cin.clear(); std::cin.ignore(10000,'\n');
                           throw MyException(ErrorType::InvalidArg,0);}
            switch(cmd){
            case 1: createObj(objs); break;
            case 2: appendObj(objs); break;
            case 3: printAll(objs);  break;
            case 4: removeObj(objs); break;
            case 5: subseqObj(objs); break;
            case 6: concatObj(objs); break;
            case 7: removeItm(objs); break;
            case 0: run=false; break;
            default: std::cout<<"Unknown\n";
            }
        }
        catch(const MyException& ex){ handleException(ex); }
    }

    for(auto& it:objs) if(it.isSeq) delete it.seq; else delete it.que;
    std::cout<<"Program finished.\n";
}


static void createSeq(std::vector<Item>& v);
static void createQue(std::vector<Item>& v);

static void createObj(std::vector<Item>& v)
{
    std::cout<<"(1)Sequence \n(2)Queue : ";
    int t; std::cin>>t;
    if(t==1) createSeq(v);
    else if(t==2) createQue(v);
    else throw MyException(ErrorType::OutOfRange,3);
}
static void createSeq(std::vector<Item>& v)
{
    std::cout<<"Seq type: \n1)Array \n2)List \n3)ImmArray \n4)ImmList : ";
    int c; std::cin>>c;
    Sequence<int>* s=nullptr;
    if(c==1) s=new ArraySequence<int>;
    else if(c==2) s=new ListSequence<int>;
    else if(c==3){ int n; std::cout<<"size="; std::cin>>n;
                   auto* buf=new int[n]; for(int i=0;i<n;++i) std::cin>>buf[i];
                   s=new ImmutableArraySequence<int>(buf,n); delete[]buf; }
    else if(c==4){ int n; std::cout<<"size="; std::cin>>n;
                   auto* buf=new int[n]; for(int i=0;i<n;++i) std::cin>>buf[i];
                   s=new ImmutableListSequence<int>(buf,n); delete[]buf; }
    else throw MyException(ErrorType::OutOfRange,3);

    v.emplace_back(s);
    std::cout<<"[OK] created seq ID="<<v.size()-1<<"\n";
}
static void createQue(std::vector<Item>& v)
{
    std::cout<<"Queue: \n1)ArrayQ \n2)Circular \n3)ArrayP \n4)ListQ \n5)ListP : ";
    int c; std::cin>>c;
    Queue<int>* q=nullptr;
    switch(c){
      case 1: q=new ArrayQueue<int>; break;
      case 2: q=new CircularArrayQueue<int>; break;
      case 3: q=new ArrayPQueue<int>; break;
      case 4: q=new ListQueue<int>; break;
      case 5: q=new ListPQueue<int>; break;
      default: throw MyException(ErrorType::OutOfRange,3);
    }
    v.emplace_back(q);
    std::cout<<"[OK] created queue ID="<<v.size()-1<<"\n";
}


static void appendObj(std::vector<Item>& v)
{
    if(v.empty()){ std::cout<<"Nothing to modify\n"; return; }
    int id=askID(v,"ID to append/enqueue");
    int val; std::cout<<"value="; std::cin>>val;

    if(v[id].isSeq){
        std::cout<<"Insert: \n1)front \n2)back \n3)index : ";
        int opt; std::cin>>opt;
        if(opt==1) v[id].seq->Prepend(val);
        else if(opt==2) v[id].seq->Append(val);
        else if(opt==3){
            int idx;
            std::cout<<"index="; 
            std::cin>>idx;
            v[id].seq->InsertAt(val,idx);
        }
        else throw MyException(ErrorType::OutOfRange,3);
    }else{
        v[id].que->Enqueue(val);
    }
}


static void removeItm(std::vector<Item>& v) {
    if(v.empty()){
        std::cout<<"Nothing\n"; 
        return;
    }
    int id=askID(v,"ID");
    if(v[id].isSeq) {
        int idx; std::cout<<"index="; std::cin>>idx;
        v[id].seq = v[id].seq->RemoveAt(idx);
    } else{
        int x=v[id].que->Dequeue();
        std::cout<<"dequeued "<<x<<"\n";
    }
}

static void subseqObj(std::vector<Item>& v) {
    int id=askID(v,"Seq ID"); if(!v[id].isSeq) throw MyException(ErrorType::InvalidArg,6);
    int s,e; std::cout<<"start end: "; std::cin>>s>>e;
    v.emplace_back( v[id].seq->GetSubsequence(s,e) );
    std::cout<<"new ID="<<v.size()-1<<"\n";
}

static void concatObj(std::vector<Item>& v) {
    int a=askID(v,"Seq A"); int b=askID(v,"Seq B");
    if(!v[a].isSeq||!v[b].isSeq) throw MyException(ErrorType::InvalidArg,6);
    v.emplace_back( v[a].seq->Concat(v[b].seq) );
    std::cout<<"new ID="<<v.size()-1<<"\n";
}

static void removeObj(std::vector<Item>& v) {
    int id=askID(v,"ID to remove");
    if(v[id].isSeq) delete v[id].seq; else delete v[id].que;
    v.erase(v.begin()+id);
    std::cout<<"removed\n";
}

static void printAll(const std::vector<Item>& v) {
    for(std::size_t i=0;i<v.size();++i){
        std::cout<<"#"<<i<<" ";
        if(v[i].isSeq){
            auto* s=v[i].seq;
            std::cout<<s->TypeName()<<" len="<<s->GetLength()<<" : ";
            for(int j=0;j<s->GetLength();++j) std::cout<<s->Get(j)<<" ";
        }else{
            auto* q=v[i].que;
            std::cout<<q->TypeName()<<" size="<<q->Size()<<" : ";
            Queue<int>* tmp=q->Clone();
            while(!tmp->IsEmpty()) std::cout<<tmp->Dequeue()<<" ";
            delete tmp;
        }
        std::cout<<"\n";
    }
}

static int askID(const std::vector<Item>& v,const char* text) {
    std::cout<<text<<" [0.."<<v.size()-1<<"]: ";
    int id; std::cin>>id;
    if(!std::cin) throw MyException(ErrorType::InvalidArg,1);
    if(id<0||id>=(int)v.size()) throw MyException(ErrorType::OutOfRange,1);
    return id;
}