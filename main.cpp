#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
std::map<std::string, std::set<std::string>> grammar;

bool verif(std::string cuvant, std::string nod)
{
    if(cuvant.empty()) {
        for (auto x: grammar[nod])
            if (x == "$")
                return true;
    }
    else if(cuvant.length() == 1)
    {
        for(auto x : grammar[nod])
            if(x == cuvant)
                return true;
    }
    for(auto x : grammar[nod])
    {
        if(cuvant[0] == x[0] && x.length() > 1)
            if(verif(cuvant.substr(1), x.substr(1,1)))
                return true;
    }

    return false;
}

int main() {
    std::ifstream in("../gramatica.in");
    std::string linie;
    while(getline(in, linie))
    {
        std::stringstream s(linie);
        std::string nod;
        s>>nod;
        std::string to;
        while(s>>to)
        {
            if(grammar[nod].empty())
                grammar.insert({nod, std::set<std::string>{}});
            grammar[nod].insert(to);
        }
    }
    for(auto x : grammar)
    {
        std::cout<<x.first<<' ';
        for(auto y : x.second)
            std::cout<<y<<' ';
        std::cout<<'\n';
    }
    std::cout<<"Scrie 'stop' pentru a opri citirea cuvintelor\n";
    std::string inp_cuv;
    while(inp_cuv != "stop")
    {
        std::getline(std::cin, inp_cuv);
        std::cout<<(verif(inp_cuv, "S") ? "Cuvant acceptat\n" : "Cuvant neacceptat\n");
    }

    return 0;
}
