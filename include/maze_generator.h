#pragma once

#include <stdio.h>
#include <string>
#include <vector>

using std::string;

class Maze_Gen {
    public:
        //constructor
        Maze_Gen();

        // generates random hex maze
        string generate_maze(int size = 5);

    private:
        /*  
            arbitrary different size mazes
            easy - 5x5
            mid - 8x8
            hard - 10x10
        */
        std::vector<string> easy_collection = {
            "a89c9d75754a1e14b6956be22",
            "88aa955e8375d5dd63556aa22",
            "9e88949577743ddc29436b62a",
            "9c89d415637569dd69556a362",
            "9dea942bc348a3d748b5e36a2",
            "9cabd628a1ea1e1e94b5e22b6",
            "8a9dd6b421ea1e1cb6b56aaa2"
        };
        std::vector<string> mid_collection = {
            "89c9e8895637d7754bc81ca1683777c3c2bdc9694aa216b55cab49c162be3636",
            "9e9ea9c9481de2157543cb75c35d5e835d635c2b54a823c943d6a8356a3ea3e2",
            "a9caa9e9c03dc29556835d615e0b61e3696bc1ddc0be162157dd7ca36a36a2aa",
            "89c9eaa95635dca348b614bd55ea15c177dc1555e8234375d69d6a816a23ea36",
            "8be8a9cb4bc3d74b480a28095569d75575e34a17e3de3d49e809d435e37622b6",
            "8aa9ddcb7c94343dd55681c34169762956b4a8a36bc3d5cbc94b5609762a2b76",
            "aaa89c89eaa36355dc8aa8354168b6b575e0a8b7c29695e9495d54a1777636b6"
        };
        std::vector<string> hard_collection = {
            "aa8aaaa9e9c94bcbd69574295c1e03d69555480b6a3415756bddc376b489557ddca17554a221d7d5428bd74a017e3e2a2b76",
            "88bc9cabdd749562a941c3549de2357d6355c8a1c29c3577e16b42b4bdd5dc3cb6a22156949ca9c35c1575c35d6362b76a22",
            "9dea9ca88b549e02b569435c3ca2974b63e1ea296a88b7caa3dc35de2a8941d6289e37563cb75cbd5dc0a961e16237e3e2a2",
            "89dddde8bd7602229681ea1cab5e35dc03cb4ab543681e1e816bc37d4a17cb5de14b694b60b54a956881d56b55e37762aa36",
            "88abdc8a8b769e235d4bca3c8976295c8177dc956375e81761c8a29549e175e97774a1c3e0abd4b568a2a942b5e2abe23ea2",
            "9cbe9e9ca961dc2a21d7c234bdc22969c3d41ca3c3696177e95ca0b7dc9555d7dd556143480355d55e154800176a3777776a",
            "9c8aa8bddd635c83c215cb776a1e35688bdd6a83c36941e81d5e9635c3637e0bc23de9e95e0bd5c1d55c3c34156222a2a376"
        };
};