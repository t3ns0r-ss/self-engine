// interact.hpp: the helper behind every judge (tests/judge.cpp) of an interactive code unit.
// A judge is a small program that plays the part of the judge of an interactive problem:
//   judge <hidden-test-file> <verdict-file>      (its standard input is the solution's output and the other way round)
// It reads the hidden test (the secret and the budget) from the first file, answers the queries of the solution,
// counts them, checks the final answer, and writes the verdict to the second file: a first line that starts with
// "OK" when the solution is right and inside the budget, otherwise "WA ..." (one line with the reason), then the
// transcript, one line per message ("Q ..." from the solution, "R ..." from the judge).
// scripts/interact.sh connects the solution and the judge with two pipes; a solution that does not flush its output
// leaves the judge waiting, the script stops both after a few seconds and writes "Idleness limit exceeded".
#pragma once
#include <bits/stdc++.h>

struct Judge {
    std::ifstream hidden;                   // the hidden test file: read the secret from it first
    std::string verdictPath;
    std::vector<std::string> transcript;
    int queries = 0;                        // number of queries read so far (see query())

    Judge(int argc, char** argv) {
        if (argc < 3) {
            std::cerr << "usage: judge <hidden-test-file> <verdict-file>\n";
            std::exit(2);
        }
        hidden.open(argv[1]);
        verdictPath = argv[2];
    }

    // Sends one line to the solution and flushes, as a real judge does.
    void say(const std::string& line) {
        transcript.push_back("R " + line);
        std::cout << line << std::endl;
    }

    // Reads the next line of the solution. A solution that quit early gives a verdict at once.
    std::string read() {
        std::string line;
        if (!std::getline(std::cin, line)) finish("WA the solution quit before it printed an answer");
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
        transcript.push_back("Q " + line);
        return line;
    }

    // Writes the verdict file and stops. "OK" must be the start of the first line for a right solution.
    [[noreturn]] void finish(const std::string& verdict) {
        std::ofstream out(verdictPath);
        out << verdict << "\n";
        for (const std::string& line : transcript) out << line << "\n";
        out.close();
        std::_Exit(0);
    }

    // Counts one query against the budget. Over the budget the judge sends -1, as the usual judges do.
    void query(int budget) {
        queries++;
        if (queries > budget) {
            say("-1");
            finish("WA more than " + std::to_string(budget) + " queries");
        }
    }

    // Sends -1 and ends with a wrong-answer verdict (for a malformed query).
    [[noreturn]] void reject(const std::string& reason) {
        say("-1");
        finish("WA " + reason);
    }
};
