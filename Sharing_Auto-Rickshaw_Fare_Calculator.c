/*
*   Project Title: Dynamic Fare Calculator for a Sharing Auto Rickshaw
*   Author Name: Neev Mittal
*   Project Start Date: 08-01-2025 (DD-MM-YYYY)
*   Project Completion Date: 10-01-2025 (DD-MM-YYYY)
*   Version: 1.0
*   Description: This project dynamically calculates the fare for the passengers in a sharing auto rickshaw
                 based on distance travelled and the number of passengers in the vehicle. The method ensures
                 the benifit of both- the driver and passengers.
*/


/*  The program will have a dynamic input where the distance keeps getting updated in real time.
*   The minimum fare will be 25 rupees upto 1.5 kilometers
*   For 1 passenger, the fare will be 17 rupees per kilometer
*   For 2 passengers, the fare will be 20 rupees per kilometer
*   For 3 passengers, the fare will be 24 rupees per kilometer
*   (Assume a maximum of 3 people sit in a sharing auto rickshaw)
*   The fare will be split equally for all the passengers in the rickshaw at any given moment
*   If the passenger joins the rickshaw before the minimum fare is reached, 
        the 25 rupees will be distributed among the passengers based on the time of joining.
*/


#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int update_distance(int total_distance){
    printf("Press any key to stop the auto...\n");
    while(1){
        if(_kbhit()){
            printf("\n");
            return total_distance;
        }
        printf("\rDistance = %dm", total_distance++);
        Sleep(50);
    }
}

double update_fare(int section_distance, int num_passenger, double passenger_fare[]){
    double total_fare = 0.0;
    if(num_passenger == 1){
        total_fare = ((section_distance / 1000.0) * 17);
        passenger_fare[0] = passenger_fare[0] + total_fare;
    }
    else if(num_passenger == 2){
        total_fare = ((section_distance / 1000.0) * 20);
        for(int i=0; i<num_passenger; i++){
            passenger_fare[i] = passenger_fare[i] + (total_fare / num_passenger);
        }
    }
    else if(num_passenger == 3){
        total_fare = ((section_distance / 1000.0)* 24);
        for(int i=0; i<num_passenger; i++){
            passenger_fare[i] = passenger_fare[i] + (total_fare / num_passenger);
        }
    }
    else{
        return total_fare;
    }
    return total_fare;
}

int main(){
    int num_passenger, n, total_distance=0, section_distance=0, cumulative_distance=0;
    double passenger_fare[3] = {0.0,0.0,0.0};
    double remaining_fare = 25.0;
    double total_fare = 25.0; // The minimum fare earned by the autorickshaw driver

    printf("Welcome to the Auto Rickshaw!\n");
    printf("How many people are there at the start? 1, 2 or 3?\n");
    scanf("%d", &num_passenger);

    for(int i=0; i<num_passenger; i++){
        passenger_fare[i] = total_fare / num_passenger;
    }

    printf("Starting Journey");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".\n");
    Sleep(750);

    do{
        printf("The auto rickshaw has started!\n");

        total_distance = update_distance(total_distance);
        section_distance = total_distance - cumulative_distance;
        cumulative_distance = cumulative_distance + section_distance;

        printf("\nThe current section distance = %dm\n", section_distance);
        printf("The current total distance = %dm\n", total_distance);

        if(total_distance > 1500){
            total_fare = total_fare + update_fare(section_distance, num_passenger, passenger_fare);
        }
        
l1:     printf("\n1. New Passenger\n");
        printf("2. Exiting Passenger\n");
        printf("3. Continue Journey\n");
        scanf("%d", &n);

        if(n==1){
            if(num_passenger == 3){
                printf("The auto rickshaw is already full!\n");
                Sleep(1000);
                goto l1;
            }
            num_passenger++;
            if(total_distance < 1500){
                int fare_distance = 1500-total_distance;
                passenger_fare[num_passenger-1] = fare_distance * remaining_fare / 1500.0 / num_passenger;
                for(int i=0; i<num_passenger-1; i++){
                    passenger_fare[i] = passenger_fare[i] - (passenger_fare[num_passenger-1] / (num_passenger-1));
                }
            }
        }

        else if(n==2){
            if(num_passenger > 1){
                printf("Which passenger has left?\n");
                for(int i=0; i<num_passenger; i++){
                    printf("%d. Passenger %d\n", i+1, i+1);
                }
                scanf("%d", &n);
                n--;

                printf("The fare for the leaving passenger is Rs%.2f\n", passenger_fare[n]);
                remaining_fare -= passenger_fare[n];
                passenger_fare[n] = 0.0;

                for(int i=n; i<num_passenger-1; i++){
                    passenger_fare[i] = passenger_fare[i+1];
                }
            }

            else{
                printf("The fare for the leaving passenger is Rs%.2f\n", passenger_fare[0]);
                passenger_fare[0] = 0.0;
                break;
            }
            num_passenger--;
        }

        if(n != 3){
            goto l1;
        }
        
        
    }while(num_passenger!=0);
    
    printf("The total money earned by the driver = Rs%.2lf\n", total_fare);
    return 0;
}