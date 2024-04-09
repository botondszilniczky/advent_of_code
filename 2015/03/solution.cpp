#include <iostream>
#include <fstream>
#include <map>

std::string readFile(std::string filename)
{
    std::string orders;
    std::ifstream file(filename);
    
    file >> orders;

    file.close();
    return orders;
}

void solve(std::string orders)
{
    std::map<std::pair<int,int>, int> history;
    std::pair<int,int> pos = {0,0};

    for(char order : orders)
    {
        switch (order)
        {
        case '<':
            pos.first--;
            break;
        
        case '>':
            pos.first++;
            break;
        
        case '^':
            pos.second--;
            break;
        
        case 'v':
            pos.second++;
            break;
        
        default:
            break;
        }

        if (history.find(pos) != history.end())
        {
            history[pos] += 1;
        }
        else
        {
            history[pos] = 1;
        }
        
    }
    
    std::cout << "Result 1:\t" << history.size() << std::endl;
}

void solve2(std::string orders)
{
    std::map<std::pair<int,int>, int> history;
    std::pair<int,int> pos_santa = {0,0};
    std::pair<int,int> pos_roboSanta = {0,0};

    for(size_t i = 0; i < orders.size(); i++)
    {       
        if (i % 2 == 0)
        {
            switch (orders[i])
            {
            case '<':
                pos_santa.first--;
                break;
            
            case '>':
                pos_santa.first++;
                break;
            
            case '^':
                pos_santa.second--;
                break;
            
            case 'v':
                pos_santa.second++;
                break;
            
            default:
                break;
            }
            history[pos_santa] = 0;
        }
        else
        {
            switch (orders[i])
            {
            case '<':
                pos_roboSanta.first--;
                break;
            
            case '>':
                pos_roboSanta.first++;
                break;
            
            case '^':
                pos_roboSanta.second--;
                break;
            
            case 'v':
                pos_roboSanta.second++;
                break;
            
            default:
                break;
            }
            history[pos_roboSanta] = 0;
        }
    }
    std::cout << "Result 2:\t" << history.size() << std::endl;
}

int main(int argc, char const *argv[])
{
    std::string orders = readFile("input.txt");
    solve(orders);
    solve2(orders);
    return 0;
}
