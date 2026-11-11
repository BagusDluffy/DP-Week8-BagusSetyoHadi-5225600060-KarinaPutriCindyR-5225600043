#include "PlayerInput.h"
#include <sstream>
#include <string>
#include <vector>
#include <set>

PlayerInput::PlayerInput(std::istream& in, std::ostream& out)
    : m_in(in), m_out(out) {}

void PlayerInput::displayHand(const Hand& hand) const {
    m_out << "================================\n";
    m_out << "          YOUR HAND\n";
    m_out << "================================\n\n";

    for (size_t i = 0; i < hand.cards.size(); ++i) {
        m_out << "[" << (i + 1) << "] " << hand.cards[i].toString() << "\n";
    }
    m_out << "\n";
}

ChosenHand PlayerInput::promptSelection(const Hand& availableHand) {
    while (true) {
        displayHand(availableHand);

        m_out << "Select up to 5 cards.\n";
        m_out << "Enter card indexes separated by spaces:\n";

        std::string line;
        if (!std::getline(m_in, line)) {
            // EOF or stream error - fallback select first card
            ChosenHand fallback;
            if (!availableHand.cards.empty()) {
                fallback.addCard(availableHand.cards[0]);
            }
            return fallback;
        }

        // Trim or check empty
        if (line.empty()) {
            m_out << "Please enter at least 1 card index.\n\n";
            continue;
        }

        std::istringstream iss(line);
        std::vector<int> indexes;
        int idx;
        bool parseError = false;

        while (iss >> idx) {
            indexes.push_back(idx);
        }

        // Cek jika ada sisa token non-integer
        if (!iss.eof()) {
            iss.clear();
            std::string remainder;
            if (iss >> remainder) {
                parseError = true;
            }
        }

        if (parseError) {
            m_out << "Invalid input. Please enter numeric indexes only.\n\n";
            continue;
        }

        if (indexes.empty()) {
            m_out << "Please select at least 1 card.\n\n";
            continue;
        }

        if (indexes.size() > 5) {
            m_out << "\nYou can only select up to 5 cards.\n";
            m_out << "Please select again.\n\n";
            continue;
        }

        // Validasi index range & duplicate
        std::set<int> seen;
        bool rangeError = false;
        bool duplicateError = false;

        for (int i : indexes) {
            if (i < 1 || static_cast<size_t>(i) > availableHand.cards.size()) {
                rangeError = true;
                break;
            }
            if (!seen.insert(i).second) {
                duplicateError = true;
                break;
            }
        }

        if (rangeError) {
            m_out << "Index out of range (valid: 1 to " << availableHand.cards.size() << "). Please select again.\n\n";
            continue;
        }

        if (duplicateError) {
            m_out << "Duplicate card index selected. Please select again.\n\n";
            continue;
        }

        // Tampilkan kartu yang dipilih
        m_out << "\nYour selection: ";
        for (size_t i = 0; i < indexes.size(); ++i) {
            m_out << indexes[i] << (i + 1 < indexes.size() ? " " : "");
        }
        m_out << "\n\nSelected Cards:\n";
        ChosenHand chosen;
        for (int i : indexes) {
            const Card& c = availableHand.cards[i - 1];
            chosen.addCard(c);
            m_out << c.toString() << " ";
        }
        m_out << "\n\nTotal selected: " << chosen.size() << " / 5\n\n";

        // Konfirmasi
        m_out << "Play this hand? (Y/N): ";
        std::string confirm;
        if (!std::getline(m_in, confirm)) {
            return chosen;
        }

        if (!confirm.empty() && (confirm[0] == 'Y' || confirm[0] == 'y')) {
            m_out << "\n";
            return chosen;
        }

        m_out << "Selection cancelled. Please select again.\n\n";
    }
}
