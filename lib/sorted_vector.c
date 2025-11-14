/**
 * Contains functions for the sorted vector struct
 *
 * @author: Karina Quenta
 * @class: CS 5008
 * @term: Fall 2025
**/

#include "vector.h"
#include "movie.h"
#include <strings.h>

/**
 * adds a movie to the sorted vector.
 * 
 * Based on the movie (compare_movies), it will find the correct index
 * using a linear search.
 * 
 * The moment it finds that the movie to add is greater than the
 * current movie, it will insert it at that next index calling vector_insert.
 * 
 * 
 * @param vector the vector to add the movie to
 * @param movie the movie to add
*/
void add_to_sorted_vector(SortedMovieVector * vector, Movie * movie) {
    if (!vector || !movie)
    return;
    //curr # of movies
    int n = vector->size;
    size_t index = 0;
    //as long as the movie to add is greater than curr movies, move forward
    //we stop once the condition is broken
    while (index < n){
        Movie *cur = vector_get(vector,index);
        if (compare_movies(movie, cur) > 0) {
            //keep incrementing
            index++;
        }else{
            break;
        }

    }
    vector_insert(vector,movie,index);
}

/**
 * Finds a movie in the sorted vector based on the title only of the movie.
 *
 * strcasecmp is used to compare the titles, so the search is case insensitive.
 *
 * For example: int cmp = strcasecmp(title, movie->title);
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one. 
 *
 * @param vector the vector to search
 * @param title the title of the movie to find
 * @return the movie if found, NULL otherwise
 */
Movie * find_in_sorted_vector(SortedMovieVector * vector, const char * title) {
    int left=0;
    int right = vector->size - 1;

    while (left <= right) {
        int mid = (left + right)/2;
        Movie *mid_movie = vector_get(vector,mid);
        //comparing titles and not case sensitive
        int compare = strcasecmp(title, mid_movie->title);

        if (compare == 0){
            return mid_movie;
        }else if (compare <0){
            //searching left half of movies
            right = mid - 1;
        }else{
            //searching right half of movies
            left = mid + 1;
        }
    }
    // if the movie is not found, return NULL
    return NULL;
}

/**
 * Checks if the sorted vector contains a movie with the given title.
 *
 * Very similar to find_in_sorted_vector, but instead of just finding
 * the movie will call vector_remove(vector, index) to remove the movie
 * returning the resulted removed movie.
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one.
 *
 * @param vector the vector to check
 * @param title the title to check for
 * @return the movie removed, NULL otherwise
 */
Movie* sorted_vector_remove(SortedMovieVector *vector, const char *title){
    int left = 0;
    int right = vector->size -1;

    while (left <= right){
        int mid = (left + right) /2;
        Movie *mid_movie = vector_get(vector,mid);

        int compare = strcasecmp(title,mid_movie->title);

        if(compare == 0){
            //found the movie, so remove it and return it
            return vector_remove(vector,mid);
        }
        else if (compare < 0){
            right = mid -1;
        }else{
            left = mid + 1;
        }
    }
    return NULL; // not found
}
