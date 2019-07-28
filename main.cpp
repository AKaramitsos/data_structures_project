#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <conio.h>
#include <cctype>
#include <chrono>
#include <random>

using namespace std;


typedef string date;


struct Reservation
{
    char name[56];
    date checkinDate;
    int stayDurationDays;
};

struct Hotel
{
    int id;
    char name[256];
    int stars;
    int numberOfRooms;
    Reservation *reservations;
};

struct komvos
{
    int timh;
    string hot_name;
    komvos *left;
    komvos *right;
    int height;
};
typedef struct komvos *komvosptr;

class avltree
{
public:
    void insert(int,string,komvosptr &);
    void find(int,komvosptr &);
    int f_height(komvosptr &); // find height
    komvosptr ll(komvosptr &);
    komvosptr lr(komvosptr &);
    komvosptr rr(komvosptr &);
    komvosptr rl(komvosptr &);
    int max(int,int);
};
void avltree::insert(int x,string y,komvosptr &p)
{
    if (p == NULL)
    {
        p = new komvos;
        p->timh = x;
        p->hot_name = y;
        p->left=NULL;
        p->right = NULL;
        p->height=0;
    }
    else
    {
        if (x<p->timh)
        {
            insert(x,y,p->left);
            if ((f_height(p->left) - f_height(p->right))==2)
            {
                if (x < p->left->timh)
                {
                    p = ll(p);
                }
                else
                {
                    p = lr(p);
                }
            }
        }
        else if (x>p->timh)
        {
            insert(x,y,p->right);
            if ((f_height(p->right) - f_height(p->left))==2)
            {
                if (x > p->right->timh)
                {
                    p = rr(p);
                }
                else
                {
                    p = rl(p);
                }
            }
        }
    }

    int lch,rch,mch; // left right and max child height
    lch=f_height(p->left);
    rch=f_height(p->right);
    mch=max(lch,rch);
    p->height = mch + 1;
}

void avltree::find(int x,komvosptr &p)
{

    if (p==NULL)
    {
        cout<<"Timh not found."<<endl;
    }
    else
    {
        if (x < p->timh)
        {
            find(x,p->left);
        }
        else if (x > p->timh)
        {
            find(x,p->right);
        }
        else
        {
            cout << "Hotel found:" << p->hot_name << endl;
        }
    }
}
int avltree::f_height(komvosptr &p)
{
    int t;
    if (p == NULL)
    {
        return -1;
    }
    else
    {
        t = p->height;
        return t;
    }
}

komvosptr avltree:: ll(komvosptr &temp)
{
    komvosptr p;
    p = temp->left;
    temp->left = p->right;
    p->right = temp;
    temp->height = max(f_height(temp->left),f_height(temp->right)) + 1;
    p->height = max(f_height(p->left),temp->height) + 1;
    return p;
}
komvosptr avltree:: rr(komvosptr &temp)
{
    komvosptr p;
    p = temp->right;
    temp->right = p->left;
    p->left = temp;
    temp->height = max(f_height(temp->left),f_height(temp->right)) + 1;
    p->height = max(temp->height,f_height(p->right)) + 1;
    return p;
}
komvosptr avltree:: lr(komvosptr &temp)
{
    temp->left=rr(temp->left);
    return ll(temp);
}
komvosptr avltree::rl(komvosptr &temp)
{
    temp->right = ll(temp->right);
    return rr(temp);
}
int avltree::max(int value1, int value2)
{
    return ((value1 > value2) ? value1 : value2);
}




int bin_Search(vector<int> idss, int l, int r, int hot_id) //function gia binary search
{
    if (r >= l)
    {
        int m = l + (r - l)/2;
        if (idss[m] == hot_id)
        {
            return m;
        }
        else if (idss[m] > hot_id)
        {
            return bin_Search(idss, l, m-1, hot_id);
        }
        else if (idss[m] < hot_id)
        {
            return bin_Search(idss, m+1, r, hot_id);
        }
    }
    else
    {
        return -1;
    }
}

int inter_search(vector<int> idss, int n, int x) //function gia interpolation search
{
    int l = 0;
    int r = n - 1;
    int m;

    while ((x >= idss[l]) && (x <= idss[r]))
    {
        m = l + ((x - idss[l])*(r - l)/(idss[r] - idss[l]));
        if (idss[m] < x)
        {
            l = m + 1;
        }
        else if(x < idss[m])
        {
            r = m - 1;
        }
        else if(x == idss[l])
        {
            return l;
        }
        else if(x == idss[r])
        {
            return r;
        }
        else
        {
            return m;
        }
    }
    return -1;
}


int main(int argc, char *argv[])
{
    int epilogh = 1; //gia na sunexisei h oxi h leitourgia toy programmatos
    vector<string> pinakas; //ka8e grammh tou arxeiou
    vector<string> ksenod; //ka8e ksenodoxio tou arxeiou
    vector<string> pelates;//ka8e pelaths ka8e ksenodoxiou
    ifstream myfile ("data.csv");
    int p_ksen; //plh8os ksenodoxiwn (prwth gramh tou arxeiou)
    string hotel_info; //plhrofories ksenodoxiou gia to 3
    string hotel_id;
    string reservation_info;
    int hot_id;

    string line;
    getline (myfile,line);
    string p = line.substr(0,4);
    p_ksen = atoi(p.c_str());
    string surname; // gia anazhthsh vash epi8etou
    int ans; //apanthsh gia anazhthsh sto 4
    int var=0; //gia linear search sto 4
    komvosptr root; //struct root
    avltree avl; // class object avl tree
    root = NULL;





    while(epilogh == 1)
    {

        cout << "Greetings! Please select a choice from the menu." << endl;
        cout << "1. Load Hotels and Reservations from file" << endl << "2. Save Hotels and Reservations to file" << endl << "3. Add a Hotel" << endl << "4. Search and Display a Hotel by id" << endl << "5. Display Reservations by surname search" << endl << "6. Exit" << endl;
        int choice;
        do
        {
            cin >> choice;
            if (choice < 1 || choice > 6) cout << "Invalid choice try again." << endl;
        }
        while(choice < 1 || choice > 6);




        if(choice == 1)
        {
            while(!myfile.eof())//ksenodoxeio mazi me krathseis se ena keli tou pinaka
            {
                getline (myfile,line);
                pinakas.push_back(line);
            }
            vector<string> hotels_avl; //ftiaxnw vector me ta hotels gia avl anazhthsh
            vector<int> ids_avl; //ftiaxnw ena vector me ta ids twn ksenodoxiwn gia avl anazhthsh
            for(int i=0; i<pinakas.size()-1; i++)
            {
                stringstream ss(pinakas[i]);
                string substr;
                getline( ss, substr, ';' );
                int g = atoi(substr.c_str());
                ids_avl.push_back(g);
                getline( ss, substr, ';' );
                hotels_avl.push_back(substr);
            }

            for(int i=0; i<ids_avl.size(); i++)
            {
                avl.insert(ids_avl[i],hotels_avl[i],root);
            }

        }

        if(choice == 2)
        {
            ofstream output_file("./data.csv");
            ostream_iterator<string> output_iterator(output_file, "\n");
            copy(pinakas.begin(), pinakas.end(), output_iterator);
        }
        if(choice == 3)
        {
            Hotel hot; //new hotel struct
            Reservation res;
            p_ksen++; // ta ksenodoxia auksanontai kata 1
            cout << "Please type the information about the hotel." << endl;
            cout << "Hotel name:";
            cin >> hot.name;
            cout << "Hotel stars:";
            cin >> hot.stars;
            cout << "Hotel rooms:";
            cin >> hot.numberOfRooms;
            ostringstream oss;
            oss << p_ksen << ";" << hot.name << ";" << hot.stars << ";" << hot.numberOfRooms << ";";
            hotel_info = oss.str();
            pinakas.push_back(hotel_info);

            cout << "Please type the information about its reservations." << endl;
            int ch = 0; // epilogh gia sunexish eisagwghs krathsewn

            while(ch != 2)
            {
                cout << "Guest's name:";
                cin >> res.name;
                cout << "Checkin date:";
                cin >> res.checkinDate;
                cout << "Stay duration in days:";
                cin >> res.stayDurationDays;
                oss << res.name << ";" << res.checkinDate<< ";" << res.stayDurationDays << ";" ;
                reservation_info = oss.str();
                pinakas.push_back(reservation_info);

                cout << "Do you want to add another guest? press 2 to stop or 1 to continue adding guests." << endl;
                cin >> ch;
            }

        }
        if(choice == 4)
        {

            vector<string> ids; //ftiaxnw ena vector me ta ids twn ksenodoxiwn gia searches
            for(int i=0; i<pinakas.size(); i++)
            {
                stringstream ss(pinakas[i]);
                string substr;
                getline( ss, substr, ';' );
                ids.push_back(substr);

            }
            vector<int> idss; //ftiaxnw ena pinaka me ta ids twn ksenodoxiwn gia searches
            for(int i=0; i<pinakas.size(); i++)
            {
                stringstream ss(pinakas[i]);
                string substr;
                getline( ss, substr, ';' );
                int ggg = atoi(substr.c_str());
                idss.push_back(ggg);

            }


            cout << "Press 1 for  linear search, 2 for binary search, 3 for interpolation search, 4 for AVL tree search and 5 for searches time test." << endl;
            cin >> ans;
            if(ans == 1)
            {

                cout << "Please type the id of the hotel you are looking for." << endl;
                cin >> hotel_id;

                for(int i=0; i<ids.size(); i++)
                {
                    if (hotel_id == ids[i])
                    {
                        cout << pinakas[i] << endl;
                        var++;
                    }
                }
                if (var==0) cout << "This isn't the hotel you are looking for." << endl;
            }
            else if(ans == 2)
            {
                cout << "Please type the id of the hotel you are looking for." << endl;
                cin >> hot_id;
                int n = pinakas.size();
                int result = bin_Search(idss, 0, n-1, hot_id);
                if(result != -1)
                {
                    cout << pinakas[result] << endl;
                }
                else
                {
                    cout << "No such hotel exist." << endl;
                }
            }
            else if(ans == 3)
            {
                cout << "Please type the id of the hotel you are looking for." << endl;
                cin >> hot_id;
                int n = pinakas.size();
                int result = inter_search(idss, n-1, hot_id);
                if(result != -1)
                {
                    cout << pinakas[result] << endl;
                }
                else
                {
                    cout << "No such hotel exist." << endl;
                }
            }
            else if(ans == 4)
            {
                cout << "Please type the id of the hotel you are looking for." << endl;
                cin >> hot_id;

                if (root != NULL)
                {
                    avl.find(hot_id,root);
                }


            }
            else if(ans == 5)
            {
                int re=2;
                if(re==1){
                int numb;

                std::random_device rd; // obtain a random number from hardware
                std::mt19937 eng(rd()); // seed the generator
                std::uniform_int_distribution<> distr(1,1310); // define the range

                auto start = std::chrono::high_resolution_clock::now(); //first try
                for(int n=0; n<1000; ++n)
                {
                    numb = distr(eng); // generate numbers

                    for(int i=0; i<ids.size(); i++)
                    {
                        if (numb == idss[i])
                        {

                        }
                    }
                }
                auto finish = std::chrono::high_resolution_clock::now(); //second try
                std::chrono::duration<double> elapsed = finish - start;
                std::cout << "Elapsed time: " << elapsed.count() << " s\n";
                }

                int e = 2;
                if(e==1)
                {
                    int numb;

                    std::random_device rd; // obtain a random number from hardware
                    std::mt19937 eng(rd()); // seed the generator
                    std::uniform_int_distribution<> distr(1,1310); // define the range

                    auto start = std::chrono::high_resolution_clock::now(); //first try
                    for(int n=0; n<1000; ++n)
                    {
                        numb = distr(eng); // generate numbers
                        int result = bin_Search(idss, 0, n-1, numb);

                    }
                    auto finish = std::chrono::high_resolution_clock::now(); //second try
                    std::chrono::duration<double> elapsed = finish - start;
                    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

                }

                int ez = 2;
                if(ez==1)
                {
                    int numb;
                    int n = pinakas.size();
                    int result = inter_search(idss, n-1, hot_id);

                    std::random_device rd; // obtain a random number from hardware
                    std::mt19937 eng(rd()); // seed the generator
                    std::uniform_int_distribution<> distr(1,1310); // define the range

                    auto start = std::chrono::high_resolution_clock::now(); //first try
                    for(int n=0; n<1000; ++n)
                    {
                        numb = distr(eng); // generate numbers
                        int result = inter_search(idss, n-1, numb);

                    }
                    auto finish = std::chrono::high_resolution_clock::now(); //second try
                    std::chrono::duration<double> elapsed = finish - start;
                    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

                }

                int z = 2;
                if(z==1)
                {
                    int numb;

                    std::random_device rd; // obtain a random number from hardware
                    std::mt19937 eng(rd()); // seed the generator
                    std::uniform_int_distribution<> distr(1,1310); // define the range

                    auto start = std::chrono::high_resolution_clock::now(); //first try
                    for(int n=0; n<1000; ++n)
                    {
                        numb = distr(eng); // generate numbers
                        avl.find(numb,root);

                    }
                    auto finish = std::chrono::high_resolution_clock::now(); //second try
                    std::chrono::duration<double> elapsed = finish - start;
                    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

                }

            }
        }
        if(choice == 5)
        {
            int ch;
            do
            {
                cout << "Type 1 for linear search or 2 for digital Tries search." << endl;
                cin >> ch;
            }
            while(ch != 1 && ch != 2);

            if(ch == 1)
            {
                int d=0; // metavlhth gia eksodo apo to loop
                while(d==0)
                {
                    d = 0;
                    cout << "Type the surname you are looking for." << endl;
                    cin >> surname;
                    for(int i=0; i<pinakas.size(); i++)
                    {
                        if (pinakas[i].find(surname) != string::npos)
                        {
                            stringstream ss(pinakas[i]);
                            vector<string> result;

                            while( ss.good() )
                            {
                                string substr;
                                getline( ss, substr, ';' );
                                result.push_back( substr );
                            }
                            for(int i=0; i<result.size(); i++)
                            {
                                if(result[i]==surname)
                                {
                                    cout << result[1] << " , " << result[i] << " , " << result[i+1] << " , " << result[i+2] << endl;
                                    d++;
                                }
                            }

                        }

                    }
                    if(d==0) cout << "No such surname exists in  our data." << endl;
                }
            }
            else if(ch == 2)
            {
                for(int i=0; i<pinakas.size(); i++)
                {
                    stringstream sss(pinakas[i]);

                    string substri;
                    getline( sss, substri, ';' );
                    getline( sss, substri, ';' );
                    ksenod.push_back( substri );
                }
                for(int i=0; i<pinakas.size(); i++)
                {
                    stringstream s(pinakas[i]);

                    string subst;
                    for(int i=0; i<4; i++)
                    {
                        getline(s,subst,';');
                    }
                    getline(s,subst,';');
                    pelates.push_back(subst);
                    for(int i=0; i<15; i++) //16 pelates exei to ka8e ksenodoxeio
                    {
                        getline(s,subst,';');
                        getline(s,subst,';');
                        getline(s,subst,';');
                        pelates.push_back(subst);
                    }
                }

                cout << "Type the surname you are looking for." << endl;
                cin >> surname;


            }
        }
        if(choice == 6)
        {
            cout << "Take care now." << endl;
            myfile.close();
            root = NULL;
            return 0;

        }
        do
        {
            cout << "Do you want to continue? Press 1 to continue or 2 to exit." << endl;
            cin >> epilogh;

        }
        while(epilogh != 1 && epilogh != 2);
    }






    root = NULL; //apodesmeush tou avl dentrou
    myfile.close();
    return 0;
}

