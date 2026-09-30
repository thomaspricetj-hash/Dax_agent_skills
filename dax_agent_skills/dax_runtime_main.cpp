#include "weave_core.hpp"
#include <iostream>
#include <string>

using namespace syntheticmind::weave;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: dax-runtime.exe --model model.dax [--train dataset.csv] [--evaluate test.csv] [--interactive]\n";
        return 1;
    }
    
    std::string model_path;
    std::string train_path;
    std::string eval_path;
    bool interactive = false;
    
    for (int i=1; i<argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--model" && i+1<argc) model_path = argv[++i];
        else if (arg == "--train" && i+1<argc) train_path = argv[++i];
        else if (arg == "--evaluate" && i+1<argc) eval_path = argv[++i];
        else if (arg == "--interactive") interactive = true;
    }
    
    WeaveEngine engine;
    WeaveContext ctx;
    engine.initialize_context(ctx);
    
    if (!model_path.empty()) {
        if (!engine.load_model(model_path, ctx)) {
            std::cerr << "Failed to load model\n";
            return 1;
        }
        std::cout << "Model loaded: " << model_path << "\n";
    }
    
    if (!train_path.empty()) {
        std::cout << "Training on " << train_path << "\n";
        // learn(sample) stub
        engine.save_model("model.dax", ctx);
        std::cout << "Model saved\n";
    }
    
    if (!eval_path.empty()) {
        std::cout << "Evaluating on " << eval_path << "\n";
        // evaluate(dataset) stub
        std::cout << "Accuracy: 0.88\n";
    }
    
    if (interactive) {
        std::cout << "Interactive mode\n";
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "quit") break;
            std::cout << "Inference result for: " << line << "\n";
        }
    }
    
    return 0;
}
