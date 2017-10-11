//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_IALGO_H
#define EDSP_IALGO_H

#include "config.h"
#include "base/interface/iinitializer.h"
#include "base/interface/ierrornotifier.h"

EDSP_BEGING_NAMESPACE

class AlgorithmTemplate : public IErrorNotifier, public IInitializer {
public:
    AlgorithmTemplate();
    virtual ~AlgorithmTemplate() { }

    inline bool isInitialized() const override { return state; }
    inline bool hasError() const override { return err.id() != EDSP_INVALID; }
    inline const Error& error() const override { return err; }
    inline const std::string& errorDescription() const override { return err.description(); }
    inline int16 errorId() const override { return err.id(); }

protected:
    virtual void initialize(bool state) override { AlgorithmTemplate::state = state; }
    virtual void setError(const Error& error) override  { AlgorithmTemplate::err = error; }

private:
    Error err;
    bool state;
};

EDSP_END_NAMESPCE

#endif //EDSP_IALGO_H
