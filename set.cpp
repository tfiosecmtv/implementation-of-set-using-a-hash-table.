/*
 * set.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: benja
 */

#include "set.h"

// From previous task:

bool equal( const std::string& s1, const std::string& s2 )
{
    size_t i=0,eq=0;
    if (s1.size()!=s2.size())
    {
        return false;
    } else
    {
        while (s1[i]!='\0')
        {
            char c1 = _tolower(s1[i]);
            char c2 = _tolower(s2[i]);
            if (c1==c2)
            {
                eq++;
            }
            i++;
        }
        
        if (eq==i)
        {
            return true;
        }
    }
    return false;
}

// Must be new written:
// It is important that equal and hash agree. That means:
//    If equal(s1,s2) then hash(s1) == hash(s2).

size_t hash( const std::string& st )
{
    size_t i = 0;
    size_t hash_number = 0;
    while (st[i]!='\0')
    {
        char c = tolower(st[i]);
        hash_number = hash_number*349+c;
        i ++;
    }
    return hash_number;
}

bool set::contains( const std::string& s ) const
{
    size_t index = hash(s) % buckets.size();
    for (auto it = buckets[index].cbegin(); it != buckets[index].cend(); ++ it)
    {
        if (equal(*it, s))
        {
            return true;
        }
    }
    return false;
}

bool set::simp_insert( const std::string& s )
{
    if (this->contains(s) == true)
    {
        return false;
    } else
    {
        size_t index = hash(s) % buckets.size();
        buckets[index].push_back(s);
        set_size++;
        return true;
    }
    
}

bool set::insert( const std::string& s )
{
    if (simp_insert(s) == false)
    {
        return false;
    } else if (max_load_factor > set_size/buckets.size())
    {
        return true;
    } else
    {
        rehash(buckets.size());
        return true;
    }
}

void set::rehash( size_t newbucketsize )
{
    if( newbucketsize < 4 )
        newbucketsize = 4;
    
    newbucketsize *= 2;
    std::vector< std::list< std::string >> newbuckets ( newbucketsize );
    for (size_t i = 0; i < buckets.size(); ++ i)
    {
        for(auto &str: buckets[i])
            newbuckets[hash(str)%newbucketsize].push_back(str);
    }
    
    buckets = newbuckets;
}

bool set::remove( const std::string& s )
{
    size_t index = hash(s) % buckets.size();
    if (this->contains(s))
    {
        auto it = buckets[index].cbegin();
        while (equal(*it, s) != true)
        {
            it ++;
        }
        buckets[index].erase(it);
        set_size --;
        return true;
    }
    return false;
}

void set::clear( )
{
    for (size_t i = 0; i < buckets.size(); ++ i)
    {
        buckets[i].clear();
    }
    set_size = 0;
}

std::ostream& set::print( std::ostream& out ) const
{
    for (size_t i = 0; i < buckets.size(); ++ i)
    {
        std::cout << "{ ";
        for (auto it = buckets[i].cbegin(); it != buckets[i].cend(); ++ it)
        {
            std::cout << *it << " ";
        }
        std::cout<< "}" <<std::endl;
    }
    return out;
}



std::ostream& set::printstatistics( std::ostream& out ) const
{
    std::cout << "set size =            " << size( ) << "\n";
    std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
    std::cout << "standard deviation =  " << standarddev( ) << "\n";
    return out;
}


