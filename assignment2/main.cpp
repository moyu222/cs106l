/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <sstream>

std::string kYourName = "Michael Zhang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::ifstream ifs{filename};
  std::set<std::string> name_set;
  std::string name;
  while (getline(ifs, name)) {
    name_set.insert(name);
  }
  return name_set;
}

std::string get_initials(const std::string& name) {
  std::istringstream iss(name);
  std::string first, second;
  if (iss >> first >> second) {
    return std::string{first[0], second[0]};
  }
  return "";
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> matches;

  // for (auto it = students.begin(); it != students.end(); ++it) {
  //   const auto& student = *it;
  //   if (student[0] == name[0]) {
  //     matches.push(&student);
  //   }
  // }

  std::string target_initials = get_initials(name);

  for (const auto& student : students) {
    if (get_initials(student) == target_initials) {
      matches.push(&student);
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  int index = matches.size() / 2;
  for (int i = 0; i < index; i++) {
    matches.pop();
  }
  return *matches.front();
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
