#ifndef SOURCE_DRUMKIT_INSTRUMENTS_NODE_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_NODE_H_

#include "../../Util/Xml.h"
#include "../../Sound/Sound.h"
#include "../../DrumKit/Triggers/Triggers/Trigger.h"

#include <vector>
#include <string>
#include <variant>
#include <any>

namespace DrumKit
{

    using NodeParams = Util::XmlElement;
    using TriggerPtrOrSoundId = std::variant<int, DrumKit::TriggerPtr>;

    class Node
    {
    
    public:

        Node(const NodeParams& params);
        virtual ~Node();
    
        virtual void SetInputs(const std::vector<TriggerPtrOrSoundId>& inputs);


    private:
        
        std::vector<TriggerPtrOrSoundId> inputs;
        std::vector<int> outputSounds;
        std::vector<std::any> inputParams;
        std::vector<std::any> internalParams;

    };
}

#endif