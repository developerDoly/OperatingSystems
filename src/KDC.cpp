//
// Created by Doly Rakotomaheninna on 10/22/19.
//

//This is acting as a server.

//has master key for UserA and another master key for UserB

//gets request from UserA

//sends back a message to UserA that is encrypted using UserA's master key
//The message also contains the same request that UserA sent to the KDC as well as the session key and the N1
//Also an encrypted ticket that is secured using UserB's master key. This ticket contains the session key and the id of UserA
//E(K_A, K_S | Request | N_1 | E(K_B, K_s | "UserA"))

//go to UserA