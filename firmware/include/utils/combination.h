#ifndef COMBINATION_H
#define COMBINATION_H



class combination
{
public:
    combination();
    ~combination() = default;
public:
    int get_id_index();
    void reset();
    void add(int id);
    bool is_correct();
    int current_ids[6];
private:
    int correct_ids[6];
    int id_index = 0;
};


#endif // COMBINATION_H