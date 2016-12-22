/**
 * Copyright (c) 2013-2016, Nima Khalilzad   <nkhal@kth.se>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>
#include <functional>

#include "../exceptions/runtimeexception.h"
#include "particle.hpp"
using namespace std;

struct ParetoFront
{
    ParetoFront(int no_obj);
    vector<Position> pareto;
    /**
     * returns true if the input position dominates the current position
     * with respect to objective obj.
     */ 
    bool dominate(Position&, int);
    /**
     * Compares the input position with the current front 
     * and replaces if it dominates
     */ 
    void update_pareto(Position);
    friend std::ostream& operator<< (std::ostream &out, const ParetoFront &p);
};
class Swarm{
public: 
    Swarm(shared_ptr<Mapping>, shared_ptr<Applications>);
    ~Swarm();
    void search();
    friend std::ostream& operator<< (std::ostream &out, const Swarm &swarm);
private:    
    shared_ptr<Mapping> mapping;
    shared_ptr<Applications> applications;
    vector<shared_ptr<Particle>> particle_set;
    const size_t no_objectives; /**< total number of objectives. */
    const size_t no_particles; /**< total number of particles. */
    const size_t no_generations; /**< total number of particles. */
    ParetoFront pareto;
    int random_obj();/** returns a random objective. */
};

