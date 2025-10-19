#include "resources.h"

int main() {
    system("cls");
    int seriesCount;
    float totalResistance = 0.0f;
    vector<Data2> resistorGroups;

    cout << "Enter total number of resistor groups in series:\t";
    cin >> seriesCount;

    ofstream tempFile("temp.txt");
    tempFile << seriesCount << endl;
    tempFile.close();

    // Gather data for each series group
    for (int i = 0; i < seriesCount; i++) {
        resources resGroup;
        totalResistance += resGroup.calcnetres(resGroup.no);
    }

    cout << "\nTotal Resistance (Series + Parallel): " << totalResistance << endl;

    // Read resistor data from file
    fstream fileIn("temp.txt", ios::in);
    string line;
    getline(fileIn, line);
    const int groupCount = stoi(line);
    vector<int> parallelCounts;

    for (int i = 0; i < groupCount; i++) {
        Data2 data;
        getline(fileIn, line);
        stringstream ss(line);
        string word;
        int resistorCount = 0;

        while (getline(ss, word, ',')) {
            data.resinpar2.push_back(stof(word));
            resistorCount++;
        }

        parallelCounts.push_back(resistorCount);
        resistorGroups.push_back(data);
    }

    // Get voltage input and compute total current
    float voltage;
    cout << "\nEnter voltage:\t";
    cin >> voltage;

    float netCurrent = voltage / totalResistance;

    // Compute current through each resistor
    vector<Data3> currents;
    for (int i = 0; i < groupCount; i++) {
        Data3 currentGroup;
        float sumReciprocal = 0.0f;

        for (float resistance : resistorGroups[i].resinpar2)
            sumReciprocal += reci(resistance);

        for (float resistance : resistorGroups[i].resinpar2)
            currentGroup.current23.push_back((netCurrent * reci(sumReciprocal)) / resistance);

        currents.push_back(currentGroup);
    }

    // Compute potential difference and power for each resistor
    vector<Data4> voltDrops;
    vector<Data5> powers;

    for (int i = 0; i < groupCount; i++) {
        Data4 vGroup;
        Data5 pGroup;

        for (size_t j = 0; j < resistorGroups[i].resinpar2.size(); j++) {
            float voltageDrop = resistorGroups[i].resinpar2[j] * currents[i].current23[j];
            vGroup.pds12.push_back(voltageDrop);
            pGroup.power1234.push_back(voltageDrop * currents[i].current23[j]);
        }

        voltDrops.push_back(vGroup);
        powers.push_back(pGroup);
    }

    system("cls");

    // Display all resistor details
    int counter = 0;
    for (int i = 0; i < groupCount; i++) {
        for (int j = 0; j < parallelCounts[i]; j++) {
            cout << "\nResistor " << counter + 1 << " details:\n";
            cout << "Resistance: " << resistorGroups[i].resinpar2[j] << " Ohm\n";
            cout << "Current: " << currents[i].current23[j] << " A\n";
            cout << "Voltage Drop: " << voltDrops[i].pds12[j] << " V\n";
            cout << "Power: " << powers[i].power1234[j] << " W\n";
            counter++;
        }
    }

    float totalPower = (netCurrent * netCurrent) * totalResistance;
    cout << "\nNet Resistance: " << totalResistance << " Ohm"
        << "\nNet Current: " << netCurrent << " A"
        << "\nNet Voltage: " << voltage << " V"
        << "\nNet Power: " << totalPower << " W\n";

    // Prepare data for visualization
    vector<string> resList, curList, volList, powList;
    vector<string> sResList, sCurList, sVolList, sPowList;

    for (int i = 0; i < groupCount; i++) {
        float groupVoltage = 0.f;
        float groupCurrent = 0.f;

        for (int j = 0; j < parallelCounts[i]; j++) {
            groupVoltage = voltDrops[i].pds12[j];
            groupCurrent += currents[i].current23[j];

            resList.push_back(to_string(resistorGroups[i].resinpar2[j]));
            curList.push_back(to_string(currents[i].current23[j]));
            volList.push_back(to_string(voltDrops[i].pds12[j]));
            powList.push_back(to_string(powers[i].power1234[j]));
        }

        sResList.push_back(to_string(groupVoltage / groupCurrent));
        sCurList.push_back(to_string(groupCurrent));
        sVolList.push_back(to_string(groupVoltage));
        sPowList.push_back(to_string(groupVoltage * groupCurrent));
    }

    system("pause");

    // Launch visualization
    Nodes nodes(
        resList, curList, volList, powList,
        totalResistance, netCurrent, voltage, totalPower,
        sResList, sCurList, sVolList, sPowList
    );

    // Visualization loop
    while (nodes.running()) {
        nodes.update();
        nodes.render();
    }

    return 0;
}
