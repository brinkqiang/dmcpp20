
#include <string>
#include <vector>
#include <iostream>

struct Inner{
	std::string name;
	std::string pdf;
};

struct Out{
	std::string code;
	std::vector<Inner> inners;
};

std::vector<Out*> f1()
{
    std::vector<Out*> res;

    for (size_t i = 0; i < 2; i++)
    {
        Out* p = new Out;
        p->code = "hello";
        res.push_back(p);

        Inner in;
        in.name = "1";
        in.pdf = "goooood";
        p->inners.push_back(in);
    }
    
    return res;
}

int main()
{
    std::vector<Out> v;

    auto res = f1();

    for (auto o : res)
    {
        Out obj = *o;
        v.push_back(obj);
        delete o;
    }
    
    for (auto o : v)
    {
        std::cout << o.code << std::endl;

        for (auto in : o.inners)
        {
            std::cout << in.name << ":" << in.pdf << std::endl;
        }
        
    }
    return 0;
}

