#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Employee
{
public:
    string name;
    string bio;
    string manager_id;
    string id;

    Employee() {}

    Employee(string id, string name, string bio, string manager_id)
    {
        this->id = id;
        this->name = name;
        this->bio = bio;
        this->manager_id = manager_id;
    }
};

size_t calc_hash(string thing)
{
    hash<string> hasher;
    return hasher(thing);
}

size_t calc_hash_emp(Employee emp)
{
    return calc_hash(emp.id);
}

class IndexEntry
{
    Employee emp;
    unsigned int bucket;
    bool valid;

public:
    IndexEntry(Employee emp, unsigned int bucket)
    {
        this->emp = emp;
        this->bucket = bucket;
        this->valid = true;
    }

    IndexEntry()
    {
        this->valid = false;
    }

    unsigned int get_bucket()
    {
        return this->bucket;
    }

    Employee get_employee()
    {
        return this->emp;
    }

    bool is_valid()
    {
        return this->valid;
    }
};

class EmployeeIndex
{
    vector<vector<Employee>> map;
    int buckets;
    bool valid = false;

public:
    EmployeeIndex()
    {
        this->buckets = 1;
        this->map = vector<vector<Employee>>();
        this->map.resize(1);
        this->map[0].resize(4);
    }

    EmployeeIndex(int buckets)
    {
        this->buckets = buckets;
        this->map = vector<vector<Employee>>();
        this->map.resize(buckets);
        for (int i = 0; i < this->buckets; i++)
        {
            map[i].resize(4);
        }
    }

    EmployeeIndex(vector<IndexEntry> entries)
    {
        unsigned int max_bucket = 1;
        for (int i = 0; i < entries.size(); i++)
        {
            if (entries[i].get_bucket() > max_bucket)
            {
                max_bucket = entries[i].get_bucket();
            }
        }

        vector<vector<Employee>> new_map = vector<vector<Employee>>();
        new_map.resize(max_bucket);
        for (int i = 0; i < entries.size(); i++)
        {
            new_map[entries[i].get_bucket()].push_back(entries[i].get_employee());
        }

        this->map = new_map;
        this->buckets = max_bucket;
        this->valid = true;
    }

    void insert(Employee emp)
    {
        // cout << "Inserting: " << emp.id << " " << emp.name << " " << emp.bio << " " << emp.manager_id << endl;
        this->valid = true;
        size_t hash = calc_hash_emp(emp);
        unsigned int bucket_idx = hash % this->buckets;
        if (this->map[bucket_idx].size() < 4)
        {
            this->map[bucket_idx].push_back(emp);
        }
        else
        {
            grow_and_insert(emp);
        }
    }

    void grow_and_insert(Employee emp)
    {
        // cout << "Growing and Inserting: " << emp.id << " " << emp.name << " " << emp.bio << " " << emp.manager_id << endl;
        vector<Employee> all_employees = vector<Employee>();
        for (int i = 0; i < this->map.size(); i++)
        {
            for (int j = 0; j < this->map[i].size(); j++)
            {
                // cout << "Extracting '" << this->map[i][j].id << "'" << endl;
                all_employees.push_back(this->map[i][j]);
            }
        }

        // cout << "Extracted all employees from map." << endl;

        vector<vector<Employee>> new_map = vector<vector<Employee>>();
        for (int i = 0; i < all_employees.size(); i++)
        {
            Employee emp = all_employees[i];
            size_t hash = calc_hash_emp(emp);
            unsigned int bucket_idx = hash % this->buckets;
            if (this->map[bucket_idx].size() < 4)
            {
                this->map[bucket_idx].push_back(emp);
            }
        }

        this->valid = true;
        this->buckets++;
    }

    void set_map(EmployeeIndex emp)
    {
        this->valid = emp.is_valid();
        this->map = emp.get_map();
    }

    vector<vector<Employee>> get_map()
    {
        return this->map;
    }

    vector<IndexEntry> into_tuple_list()
    {
        vector<IndexEntry> ent = vector<IndexEntry>();
        for (int i = 0; i < this->map.size(); i++)
        {
            for (int j = 0; j < this->map[i].size(); j++)
            {
                IndexEntry entry = IndexEntry(this->map[i][j], i);
                ent.push_back(entry);
            }
        }

        return ent;
    }

    IndexEntry lookup(string lookupid)
    {
        size_t strhash = calc_hash(lookupid);

        unsigned int bucket_idx = strhash % this->buckets;
        for (int i = 0; i < this->map[bucket_idx].size(); i++)
        {
            if (this->map[bucket_idx][i].id == lookupid)
            {
                return IndexEntry(this->map[bucket_idx][i], i);
            };
        }

        return IndexEntry(); // Invalid version
    }

    bool is_valid()
    {
        return this->valid;
    }
};


void write_index(EmployeeIndex index)
{
    vector<IndexEntry> tuples = index.into_tuple_list();
    ofstream file("./EmployeeIndex");

    for (int i = 0; i < tuples.size(); i++)
    {
        Employee emp = tuples[i].get_employee();
        file << to_string(tuples[i].get_bucket()) << "|" << emp.id << "," << emp.name << "," << emp.bio << "," << emp.manager_id << endl;
    }

    file.close();
}

EmployeeIndex read_index(string path)
{
    ifstream file(path);
    string line;

    vector<IndexEntry> entries;

    while (getline(file, line))
    {
        stringstream ss(line);
        string bucket_str;
        getline(ss, bucket_str, '|');
        unsigned int bucket_id = stoi(bucket_str);

        string id;
        getline(ss, id, ',');

        string name;
        getline(ss, name, ',');

        string bio;
        getline(ss, bio, ',');

        string manager_id;
        getline(ss, manager_id);

        entries.push_back(IndexEntry(Employee(id, name, bio, manager_id), bucket_id));
    }

    EmployeeIndex index = EmployeeIndex(entries);
}

EmployeeIndex read_csv(string path)
{
    ifstream file(path);
    if (file.fail()) {
        return EmployeeIndex();
    }
    cout << "Loaded file from path: " << path << endl;

    vector<Employee> entries;
    string line;

    while (getline(file, line))
    {
        string copied_line;

        cout << "Got line: " << line << endl;
        if (line.length() == 0) { break; }
        stringstream ss(line);

        string id;
        getline(ss, id, ',');

        string name;
        getline(ss, name, ',');

        string bio;
        getline(ss, bio, ',');

        string manager_id;
        getline(ss, manager_id);


        entries.push_back(Employee(id, name, bio, manager_id));
    }

    for (int i = 0; i < entries.size(); i++)
    {
        cout << "ID: '" << entries[i].id << "'" <<  endl;
    }

    cout << "All lines processed." << endl;

    EmployeeIndex index = EmployeeIndex();
    for (int i = 0; i < entries.size(); i++)
    {
        index.insert(entries[i]);
    }

    for (int i = 0; i < index.get_map().size() ; i++) {
        for (int j = 0; i < index.get_map()[i].size() ; i++) {
            cout << "Index in Map: " << index.get_map()[i][j].id << " " << index.get_map()[i][j].name << " " << index.get_map()[i][j].bio << " " << index.get_map()[i][j].manager_id << endl;
        }
    }

    return index;
}


int main(int argc, char *argv[])
{
    //cout << argc << endl;
    //for (int i = 0; i < argc; i++) {
    //	cout << i << ":\t'" << argv[i] << "'" << endl;
    //}

    if (argc == 2 && strcmp(argv[1], "C") == 0)
    {
        cout << "Loading from CSV and creating the index." << endl;
        EmployeeIndex indx = read_csv("./Employee.csv");
        cout << "Please check for EmployeeIndex file in the current directory." << endl;
        write_index(indx);
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "L") == 0) {

        EmployeeIndex indx = read_index("./EmployeeIndex");
        if (!indx.is_valid()) {
            indx = read_csv("./Employee.csv");
            write_index(indx);
        }

        if (!indx.is_valid()) {
            cout << "Had an error reading the index, please try re-creating or checking Employee.csv and EmployeeIndex" << endl;
            return 2;
        }

        IndexEntry lookup = indx.lookup(argv[2]);
        if (!lookup.is_valid()) {
            cout << "Couldn't find entry with hash " << argv[2] << "." << endl;
            return 3;
        }

        Employee emp = lookup.get_employee();
        cout << "Entry:" << endl << "\tid: " << emp.id << endl << "\tname: " << emp.name << endl << "\tbio: " << emp.bio << endl << "\tmanager_id" << emp.manager_id << endl;
        return 0;
    }

    cout << "Usage:" << endl << "\teindex C" << endl << "\teindex L [hash_lookup]" << endl;

    return 4;
}
