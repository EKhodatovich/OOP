#pragma once
#include <exception>

class ParserExceptions : public std::exception {};


class DifferentStringSizeException final : public ParserExceptions
{
public:
    const char* what() const noexcept override { return "One of strings in labyrinth has not the same size as others"; }
};

class EmptyStringException final : public ParserExceptions
{
public :
    const char* what() const noexcept override { return "One of strings in labyrinth is empty"; }
};



class WrongCellTypeException final : public std::exception
{
public:
    const char* what() const noexcept override { return "One of cells in labyrinth has unknown type"; }
};



class MazeExceptions : public std::exception {};

class EmptyMazeException final : public MazeExceptions
{
public:
    const char* what() const noexcept override { return "Labyrinth is too small"; }
};



class CellTableExceptions : public std::exception {};


class WrongStartPosition final : public CellTableExceptions
{
public:
    const char* what() const noexcept override { return "Start is out of labyrinth"; }
};
class WrongFinishPosition final : public CellTableExceptions
{
public:
    const char* what() const noexcept override { return "Finish is out of labyrinth"; }
};


class DifferentSizesException final : public MazeExceptions, public CellTableExceptions
{
public:
    const char* what() const noexcept override { return "Size of vector differs from (width*height)"; }
};
