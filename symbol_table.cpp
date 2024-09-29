#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

struct SymbolTableEntry {
    string name;
    string type;
    string size;
    string dimension;
    string line_of_code;
    string address;
};


class SymbolTable {
    int table_size;
    vector<list<SymbolTableEntry>> table; 

public:
    SymbolTable(int size) {
        table_size = size;
        table.resize(size);
    }
    int getHashKey(string name) {
        int hash_value = 0;
        for (char ch : name) {
            hash_value += ch;
        }
        return hash_value % table_size;
    }
    void insert(string name, string type, string size, string dimension, string line_of_code, string address) {
        int hash_key = getHashKey(name);

        for (auto &entry : table[hash_key]) {
            if (entry.name == name) {
                cout << "Symbol '" << name << "' already exists. Use update to modify it.\n";
                return;
            }
        }
        SymbolTableEntry new_entry = { name, type, size, dimension, line_of_code, address };

        table[hash_key].push_back(new_entry);
        cout << "Symbol '" << name << "' inserted.\n";
    }

    SymbolTableEntry* search(string name) {
        int hash_key = getHashKey(name);

        for (auto &entry : table[hash_key]) {
            if (entry.name == name) {
                return &entry;
            }
        }
        cout << "Symbol '" << name << "' not found.\n";
        return nullptr;
    }

    void deleteSymbol(string name) {
        int hash_key = getHashKey(name);

        for (auto it = table[hash_key].begin(); it != table[hash_key].end(); ++it) {
            if (it->name == name) {
                table[hash_key].erase(it);
                cout << "Symbol '" << name << "' deleted.\n";
                return;
            }
        }
        cout << "Symbol '" << name << "' not found.\n";
    }

    void update(string name, string type = "", string size = "", string dimension = "", string line_of_code = "", string address = "") {
        int hash_key = getHashKey(name);

        for (auto &entry : table[hash_key]) {
            if (entry.name == name) {
                if (!type.empty()) entry.type = type;
                if (!size.empty()) entry.size = size;
                if (!dimension.empty()) entry.dimension = dimension;
                if (!line_of_code.empty()) entry.line_of_code = line_of_code;
                if (!address.empty()) entry.address = address;
                cout << "Symbol '" << name << "' updated.\n";
                return;
            }
        }
        cout << "Symbol '" << name << "' not found.\n";
    }

    void show() {
        cout << "Symbol Table Contents:\n";
        for (int i = 0; i < table_size; i++) {
            if (!table[i].empty()) {
                cout << "Index " << i << ":\n";
                for (auto &entry : table[i]) {
                    cout << "Name: " << entry.name << ", Type: " << entry.type << ", Size: " << entry.size
                         << ", Dimension: " << entry.dimension << ", Line of Code: " << entry.line_of_code
                         << ", Address: " << entry.address << "\n";
                }
            }
        }
    }
};

int main() {
    SymbolTable symbolTable(10);

    symbolTable.insert("x", "ID", "2", "1", "5", "0x6dfed4");
    symbolTable.insert("Age", "Int", "2", "0", "3", "0x7ffdd8747");
    symbolTable.insert("y", "ID", "4", "1", "10", "0x7ffdd7f54");

    symbolTable.show();

    SymbolTableEntry* symbol = symbolTable.search("x");
    if (symbol) {
        cout << "Symbol found: Name: " << symbol->name << ", Type: " << symbol->type << "\n";
    }

    symbolTable.update("x", "ID", "3", "", "", "0x7ffdd0000");

    symbolTable.deleteSymbol("y");

    symbolTable.show();

    return 0;
}
