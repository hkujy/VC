#ifndef BPR_FNC_
#define BPR_FNC_

#include "LinkFnc.h"

/** \brief This class implements BPR link cost function.
	\details The equation is as follows:
	\f$t(x) = freeFlow*(1 + B*\left(\frac{x}{capacity}\right)^{power})\f$.
	This class has some numerical constants directly incorporated in code - in order to prevent floating
	point problems when evaluating first and second derivatives.
 */
class BprFnc : public LinkFnc {
	
	public:
	
		BprFnc(FPType freeFlow, FPType B, FPType capacity, FPType power);
		~BprFnc();
	
		FPType evaluate(FPType linkFlow) const;
		FPType evaluateDerivative(FPType linkFlow) const;
		FPType evaluateSecondDerivative(FPType linkFlow) const;
	
		void print() const;

		virtual std::string toString() const {
			return "BPR fnc";
		};
		
		LinkFnc* clone() const {return new BprFnc(*this);}

		FPType evaluateTimeAndDerivative(FPType linkFlow, FPType &der);

		virtual FncType getType();

		virtual FPType getCapacity();
		void setCapacity(FPType set_cap);
		void setFreeFlowTime(FPType _val);
		FPType getAlpha() const { return B_; }
		FPType getPower() const { return power_; }
		FPType getFreeFlowTime() const { return freeFlow_; }

			
		//int getNodeFrom() const;

	
	private:
	
		const FPType power_;
		const FPType B_;
		FPType freeFlow_;
		FPType capacity_;

};

#endif
