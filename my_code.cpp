#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int MAX_CANDIDATES =100;

class Candidate
{
private:
    string name;
    string party;
    int votes;
public:
    Candidate() : name(""), party(""), votes(0) {}
    Candidate(string n, string p) : name(n), party(p), votes(0) {}

    string getName() const { return name; }
    string getParty() const { return party; }
    int getVotes() const { return votes; }

    void incrementVotes() { votes++; }

    void saveToFile(string electionName)
    {
        ofstream outFile("candidates.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << electionName << " " << name << " " << party << " " << votes << endl;
            outFile.close();
        }
    }

    static Candidate *loadCandidates(string electionName, int &count);
};

Candidate *Candidate::loadCandidates(string electionName, int &count)
{
    ifstream inFile("candidates.txt");
    Candidate *candidates = new Candidate[MAX_CANDIDATES];
    count = 0;

    if (inFile.is_open())
    {
        string ename, name, party;
        int votes;
        while (inFile >> ename >> name >> party >> votes)
        {
            if (ename == electionName && count < MAX_CANDIDATES)
            {
                candidates[count] = Candidate(name, party);
                for (int i = 0; i < votes; i++)
                {
                    candidates[count].incrementVotes();
                }
                count++;
            }
        }
        inFile.close();
    }
    return candidates;
}

class Election
{
protected:
    string name;
    string type;
    string startDate;
    string endDate;
    Candidate candidates[MAX_CANDIDATES];
    int candidateCount;

public:
    Election(string n, string t, string s, string e) : name(n), type(t), startDate(s), endDate(e), candidateCount(0) {}
    virtual ~Election() {}

    string getName() const { return name; }
    string getType() const { return type; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    int getCandidateCount() const { return candidateCount; }

    virtual void displayDetails() = 0;
    virtual void conductElection() = 0;
    virtual void displayResults() = 0;

    void addCandidate(string name, string party)
    {
        if (candidateCount < MAX_CANDIDATES)
        {
            candidates[candidateCount] = Candidate(name, party);
            candidateCount++;
        }
    }

    virtual void saveToFile() = 0;
    static Election *loadElection(string name);
};

class LocalElection : public Election
{
private:
    string district;

public:
    LocalElection(string n, string s, string e, string d = "Default District")
        : Election(n, "local", s, e), district(d) {}

    void displayDetails() override
    {
        cout << "\033[1;34mLocal Election: \033[0m" << name << endl;
        cout << "\033[1;34mDistrict: \033[0m" << district << endl;
        cout << "\033[1;34mPeriod: \033[0m" << startDate << " to " << endDate << endl;
    }

    void conductElection() override
    {
        cout << "\033[1;32mConducting local election for \033[0m" << district << " district" << endl;
    }

    void displayResults() override
    {
        // Implementation here
    }

    void saveToFile() override
    {
        ofstream outFile("elections.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << name << " " << type << " " << startDate << " " << endDate << " " << district << endl;
            outFile.close();
        }
    }
};

class NationalElection : public Election
{
private:
    string country;

public:
    NationalElection(string n, string s, string e, string c = "Pakistan")
        : Election(n, "national", s, e), country(c) {}

    void displayDetails() override
    {
        cout << "\033[1;34mNational Election: \033[0m" << name << endl;
        cout << "\033[1;34mCountry: \033[0m" << country << endl;
        cout << "\033[1;34mPeriod: \033[0m" << startDate << " to " << endDate << endl;
    }

    void conductElection() override
    {
        cout << "\033[1;32mConducting national election for \033[0m" << country << endl;
    }

    void displayResults() override
    {
        // Implementation here
    }

    void saveToFile() override
    {
        ofstream outFile("elections.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << name << " " << type << " " << startDate << " " << endDate << " " << country << endl;
            outFile.close();
        }
    }
};

int main()
{
    

    // Creating a Local Election for a Pakistani district
    LocalElection local("Local Election 2025", "01-01-2025", "31-01-2025", "Karachi");
    local.displayDetails();
    local.conductElection();
    local.addCandidate("Imran Khan", "PTI");
    local.addCandidate("Maryam Nawaz", "PML-N");
    local.saveToFile();

    // Creating a National Election for Pakistan
    NationalElection national("General Election 2025", "01-02-2025", "28-02-2025", "Pakistan");
    national.displayDetails();
    national.conductElection();
    national.addCandidate("Benazir Bhutto", "PPP");
    national.addCandidate("Fawad Chaudhry", "PTI");
    national.saveToFile();

    return 0;
}
