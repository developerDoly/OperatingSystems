//
// Created by Doly Rakotomaheninna on 10/23/19.
//

//This is acting as a server.

//has master key for UserB

//receives from UserA: E(K_B, K_s | "UserA")

//decrypts ticket using master key of UserB and obtains session key and verifies that id of sender is as expected

//Then UserB sends back a message to UserA that is encrypted using the session key that contains another Nonce value
//This time N_2 and id of UserB
//E(K_S, N_2 | "UserB")

//go to User A