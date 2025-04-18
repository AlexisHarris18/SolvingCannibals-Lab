#pragma once
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
class GameState {
public:
	GameState() : missionaries(0), cannibals(0), boatIsLeft(false) {}
	GameState(int missionaries, int cannibals, bool boatIsLeft) :
		missionaries(missionaries), cannibals(cannibals), boatIsLeft(boatIsLeft) {}
	int getMissionariesLeft() const { return missionaries; }
	int getCannibalsLeft() const { return cannibals; }
	bool isValidState() const {
		//Missionaries outnumber canabals on right side
		if (missionaries < cannibals && missionaries > 0) {
			return false;
		}
		//Missionaries outnumber Cannibals left isde
		if (3 - missionaries < 3 - cannibals && 3 - missionaries > 0) {
			return false;
		}
		if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals
		> 3) {
			return false;
		}
		return true;
	}
	bool isBoatLeft() const {
		return boatIsLeft;
	}
	bool operator==(const GameState other) const {
		return other.missionaries == missionaries && other.cannibals ==
			cannibals && other.boatIsLeft == boatIsLeft;
	}
	bool operator!=(GameState other) {
		return !(other == *this);
	}
	friend ostream& operator<<(ostream& out, GameState& state) {
		for (int i = 0; i < state.missionaries; i++) {
			out << "M";
		}
		for (int i = 0; i < state.cannibals; i++) {
			out << "C";
		}
		if (state.boatIsLeft) {
			out << " B~~~~~~~ ";
		}
		else {
			out << " ~~~~~~~B ";
		}
		for (int i = 0; i < (3 - state.missionaries); i++) {
			out << "M";
		}
		for (int i = 0; i < (3 - state.cannibals); i++) {
			out << "C";
		}
		return out;
	}
	bool isNeighbor(GameState other) {
		if (boatIsLeft == other.boatIsLeft) {
			return false;
		}
		int m = abs(missionaries - other.missionaries);
		int c = abs(cannibals - other.cannibals);
		int boat = m + c;
		if (boat > 2) {
			return false;
		}
		return true;
	}
private:
	int missionaries;
	int cannibals;
	bool boatIsLeft;
};


namespace std {
	template<>
	struct hash<GameState> {
		size_t operator()(const GameState& state) const {
			return (hash<int>()(state.getMissionariesLeft()) << 2) ^
				(hash<int>()(state.getCannibalsLeft()) << 1) ^
				(hash<bool>()(state.isBoatLeft()));
		}
	};
}