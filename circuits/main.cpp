#include"resources.h"
int main()
{
    system("cls");
    int con;
    float netres = 0.0;
    vector<Data2> resinser;
    cout << "Enter total no of resistors in series:\t";
    cin >> con;
    ofstream file("temp.txt");
    file << con << endl;
    file.close();
    for (int i = 0; i < con; i++)
    {
        resources obj;
        netres += obj.calcnetres(obj.no);
    }
    cout << "\nTotal resistance is:\t" << netres;
    fstream file1("temp.txt", ios::in);
    string word, line;
    getline(file1, line);
    const int con1 = stoi(line);
    int con2;
    vector<int> parcount;
    for (int i = 0; i < con1; i++)
    {
        Data2 data;
        con2 = 0;
        getline(file1, line);
        stringstream obj2(line);
        while (getline(obj2, word, ','))
        {

            data.resinpar2.push_back(stof(word));
            con2++;
        }
        parcount.push_back(con2);
        resinser.push_back(data);
    }
    float voltage;
    cout << "\nEnter voltage:\t";
    cin >> voltage;
    float netcurr = voltage / netres;
    vector<Data3> currents;
    for (int i = 0; i < con1; i++)
    {
        Data3 data3;
        float tempsum = 0.0;
        for (int j = 0; j < parcount[i]; j++)
        {
            tempsum += reci(resinser[i].resinpar2[j]);
        }
        for (int k = 0; k < parcount[i]; k++)
        {
            float temp2 = (netcurr * reci(tempsum)) / (resinser[i].resinpar2[k]);
            data3.current23.push_back(temp2);
        }
        currents.push_back(data3);
    }
    vector<Data4> pds;
    vector<Data5> powers;
    for (int i = 0; i < con1; i++)
    {
        Data4 data4;
        Data5 data5;
        for (int j = 0; j < parcount[i]; j++)
        {
            float temp = (resinser[i].resinpar2[j]) * (currents[i].current23[j]);
            data4.pds12.push_back(temp);
            temp *= (currents[i].current23[j]);
            data5.power1234.push_back(temp);
        }
        pds.push_back(data4);
        powers.push_back(data5);
    }
    int totnum = 0;
    for (int i = 0; i < con1; i++)
    {
        totnum += parcount[i];
    }
    fflush(stdout);
    system("cls");
    system("cls");
    system("cls");
    int abc = 0;
    for (int i = 0; i < con1; i++)
    {

        for (int j = 0; j < parcount[i]; j++)
        {
            cout << "Resistor: " << abc + 1 << " details\n";
            cout << "Resistance: " << resinser[i].resinpar2[j] << endl;
            cout << "Current through it: " << currents[i].current23[j] << endl;
            cout << "Potential difference across it: " << pds[i].pds12[j] << endl;
            cout << "Power consumed by it: " << powers[i].power1234[j] << endl;
            abc++;
        }
    }
    float netpower = (netcurr * netcurr) * netres;
    cout << "Net Resistance: " << netres << endl;
    cout << "Net Current: " << netcurr << endl;
    cout << "Net Voltage: " << voltage << endl;
    cout << "Net Power consumed: " << netpower << endl;
    vector<string> reslis;
    vector<string> currlis;
    vector<string> vollis;
    vector<string> powlis;
    vector <string> sreslis;
    vector<string> scurrlis;
    vector<string> svollis;
    vector<string> spowlis;
    float vtemp = 0.f, itemp = 0.f;
    abc = 0;
    for (int i = 0; i < con1; i++)
    {
        vtemp = 0.f;
        itemp = 0.f;
        for (int j = 0; j < parcount[i]; j++)
        {
            vtemp = pds[i].pds12[j];
            itemp += currents[i].current23[j];
            reslis.push_back(to_string(resinser[i].resinpar2[j]));
            currlis.push_back(to_string(currents[i].current23[j]));
            vollis.push_back(to_string(pds[i].pds12[j]));
            powlis.push_back(to_string(powers[i].power1234[j]));
            abc++;
        }
        sreslis.push_back(to_string(vtemp / itemp));
        scurrlis.push_back(to_string(itemp));
        svollis.push_back(to_string(vtemp));
        spowlis.push_back(to_string(vtemp * itemp));
    }
    system("pause");
    Nodes nodes(reslis,currlis,vollis,powlis,netres,netcurr,voltage,netpower,sreslis,scurrlis,svollis,spowlis);
    //game loop
    while (nodes.running())
    {
        //Update
        nodes.update();
        //Render
        nodes.render();



    }
    return 0;
}