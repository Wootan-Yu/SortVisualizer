#include "SFML/Graphics.hpp"
#include <vector>
#include <random>
#include <iostream>

unsigned int cell_length = 100; //100
float width = 10; //10
float height = 10; //10
unsigned int origin_x = 20; //20
unsigned int origin_y = 700;

short start_cell = 1;
short end_cell = cell_length;

bool isSort = false;
bool isReset = true;
int iteration = 0;
int limit = cell_length;
int selectedIndex = 0;
int otherIndex = 0;

static void selectionSort(std::vector<short>& i_cell_nums, int iteration)
{
    int length = i_cell_nums.size();
    if (iteration < length - 1)
    {
        int min_index = iteration;
        //int j = iteration + 1;
        //if (j < length)
        for(int j = iteration + 1; j < length; j++)
        {
            if (i_cell_nums[j] < i_cell_nums[min_index])
            {
                min_index = j;
                otherIndex = min_index;
            }
        }
        std::swap(i_cell_nums[iteration], i_cell_nums[min_index]);
        selectedIndex = iteration;
    }
}

static void insertionSort(std::vector<short>& i_cell_nums, int iteration)
{
    
    int key = i_cell_nums[iteration];
    int j = iteration - 1;

    while (j >= 0 && i_cell_nums[j] > key) 
    {
        i_cell_nums[j + 1] = i_cell_nums[j];
        j--;
        selectedIndex = j;
    }
    i_cell_nums[j + 1] = key;

}

static void bubbleSort(std::vector<short>& i_cell_nums, int iteration)
{
    bool swapped = true;
    int n = i_cell_nums.size();
    while (swapped) {
        swapped = false;
        if(iteration < n - 1)
        {
            if (i_cell_nums[iteration] > i_cell_nums[iteration + 1]) {
                std::swap(i_cell_nums[iteration], i_cell_nums[iteration + 1]);
                swapped = true;
                selectedIndex = iteration + 1;
            }
        }
        n--;
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(1040, 720), "Window Title");

    window.setFramerateLimit(60);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1.f);

    std::vector<sf::RectangleShape> cell_rect;
    std::vector<short> cell_nums;

    for (size_t a = 0; a < cell_length; a++)
    {
        cell_nums.push_back(a + 1);
        cell_rect.push_back(rect);
    }

    //shuffle 1-100 values in array
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cell_nums.begin(), cell_nums.end(), g);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                std::shuffle(cell_nums.begin(), cell_nums.end(), g);
                isSort = false;
                isReset = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                isSort = true;
                isReset = false;
            }

        }

        //reset
        if (isReset)
        {
            for (size_t i = 0; i < cell_nums.size(); i++)
            {
                cell_rect[i].setFillColor(sf::Color::White);
            }
        }
        

        if (isSort)
        {
            //insertionSort(cell_nums, iteration);
            //bubbleSort(cell_nums, iteration);
            //selectionSort(cell_nums, iteration);
            

            /*std::cout << "[";
            for (int a = 0; a < cell_nums.size(); a++)
            {
                std::cout << cell_nums[a] << ", ";
            }
            std::cout << "]" << '\n';*/
        }


        window.clear(sf::Color::Black); // Color background

        for (size_t i = 0; i < cell_rect.size(); i++)
        {
            cell_rect[i].setSize(sf::Vector2f(width, -(height + cell_nums[i] * 6))); //-(height + cell_nums[i] * 5)) inverse height of cells
            cell_rect[i].setPosition(origin_x + i * width, origin_y);

            if (isSort)
            {
                cell_rect[i].setFillColor(sf::Color::White);
                if (selectedIndex == i)
                {
                    cell_rect[i].setFillColor(sf::Color::Red);
                }
                else if (otherIndex == i)
                {
                    cell_rect[i].setFillColor(sf::Color::Green);
                }
            }

            

            //if (swap) //test to see if i can "swap" the height of cells
            //{
            //    cell_rect[0].setSize(sf::Vector2f(width, -(height + cell_nums[99] * 5)));
            //    cell_rect[99].setSize(sf::Vector2f(width, -(height + cell_nums[0] * 5)));
            //}
            

            /*if (start_cell == cell_nums[i])
            {
                cell_rect[i].setFillColor(sf::Color::Green);
            }

            if (end_cell == cell_nums[i])
            {
                cell_rect[i].setFillColor(sf::Color::Red);
            }*/

            window.draw(cell_rect[i]);
        }

        window.display();
        iteration++;
        if (iteration >= limit)
        {
            iteration = 0;
        }

    }

    return 0;
}