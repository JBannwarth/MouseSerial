// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

// SignalFilter - Library to Filter Sensor Data using digital filters
// Available filters: Chebyshev & Bessel low pass filter (1st & 2nd order)

// Modified by: Jérémie Bannwarth, 04/12/2014

#include "SignalFilter.h"

// Constructor
SignalFilter::SignalFilter()
{
	_v[0]    = 0;
	_v[1]    = 0;
	_v[2]    = 0;
	_helper  = 0;
	_counter = 0;
	_filter  = 0;
	_order   = 0;
	_average = 0;
	_median  = 0;
}

// Begin function: set default filter options
void SignalFilter::begin()
{
	setFilter('c');
	setOrder(1);
}

// setFilter(char filter): Select filter: 'c' -> Chebyshev, 'b' -> Bessel
void SignalFilter::setFilter(char filter)
{
	_filter=filter;
}

// selectOrder(int order): Select filter order (1 or 2)
void SignalFilter::setOrder(int order)
{
	_order=order;
}

// printSamples: Print out some samples (for debugging)
void SignalFilter::printSamples()
{
	Serial.print(" ");
	Serial.print(_v[2]);

	Serial.print(" ");
	Serial.print(_v[1]);

	Serial.print(" ");
	Serial.print(_v[0]);
	Serial.print(" - ");
}

// Chebyshev filter
// IIR form 2 filter
int SignalFilter::runChebyshev(int data)
{
	if(_order==1)
	{
		// Ripple -3dB
		_v[0] = _v[1];
		long tmp = ((((data * 3269048L) >>  2)	// = ( 3.897009118e-1 * data)
			+ ((_v[0] * 3701023L) >> 3)			// + ( 0.2205981765*v[0])
			) + 1048576) >> 21;					// Round and downshift fixed point /2097152
		_v[1]= (int)tmp;
		return (int)( _v[0] + _v[1] );			// 2^
	}
	if(_order==2)
	{
		// Ripple -1dB
		_v[0] = _v[1];
		_v[1] = _v[2];
		long tmp = ((((data * 662828L) >>  4)	// = ( 7.901529699e-2 * data)
			+ ((_v[0] * -540791L) >> 1)			// + (-0.5157387562 * v[0])
			+ (_v[1] * 628977L)					// + ( 1.1996775682 * v[1])
			)+262144) >> 19;					// Round and downshift fixed point /524288

		_v[2]= (int)tmp;
		return (int)( (_v[0] + _v[2]) + 2 * _v[1] ); // 2^
	}
	else
	{
		return 0;
	}
}

// Bessel filter
// IIR form 2 filter
int SignalFilter::runBessel(int data)
{
	if(_order==1) 
	{
		//Alpha low 0.1
		_v[0] = _v[1];
		long tmp = ((((data * 2057199L) >>  3)	// = ( 2.452372753e-1 * data)
			+ ((_v[0] * 1068552L) >> 1)			// + ( 0.5095254495 * v[0])
			) + 524288) >> 20;					// Round and downshift fixed point /1048576
			_v[1]= (int)tmp;
		return (int)( _v[0] + _v[1] );			// 2^
	}
	if(_order==2)
	{
		//Alpha low 0.1
		_v[0] = _v[1];
		_v[1] = _v[2];
		long tmp = ((((data * 759505L) >>  4)	// = ( 9.053999670e-2 * data)
			+ ((_v[0] * -1011418L) >> 3)		// + (-0.2411407388 * v[0])
			+ ((_v[1] * 921678L) >> 1)			// + ( 0.8789807520 * v[1])
			) + 262144) >> 19;					// Round and downshift fixed point /524288

		_v[2]= (int)tmp;
		return (int)( (_v[0] + _v[2]) + 2 * _v[1] ); // 2^
	}
	else
	{
		return 0;
	}
}

// Median filter (78 bytes, 12 microseconds)
int SignalFilter::runMedian(int data)
{
	// Note:
	// quick & dirty dumb implementation that only keeps 3 samples: probably better 
	// to do insertion sort when more samples are needed in the calculation
	// or Partial sort: http://en.cppreference.com/w/cpp/algorithm/nth_element
	// On better inspection of this code... performance seem quite good
	// TODO: compare with: http://embeddedgurus.com/stack-overflow/tag/median-filter/
	_v[0] = _v[1];
	_v[1] = _v[2];
	_v[2]= data;

	// printSamples();
	if (_v[2] < _v[1])
	{
		if (_v[2] < _v[0])
		{
			if (_v[1] < _v[0])
			{
				_median = _v[1];
			}
			else
			{
				_median = _v[0];
			}
		}
		else
		{
			_median = _v[2];
		}
	}
	else
	{
		if (_v[2] < _v[0])
		{
			_median = _v[2];
		}
		else
		{
			if (_v[1] < _v[0])
			{
				_median = _v[0];
			}
			else
			{
				_median = _v[1];
			}
		}
	}
	return (_median);
}

int SignalFilter::run(int data)
{
	//  Uncomment for debugging
	//  Serial.println(_filter);
	//  Serial.println(_order);

	// Chebyshev filters
	if (_filter=='c')
	{
		return runChebyshev(data);
	}

	// Bessel filters
	else if (_filter=='b')
	{
		return runBessel(data);
	}

	// Median filters (78 bytes, 12 microseconds)
	else if (_filter=='m')
	{
		return runMedian(data);
	}

	return 0; // Should never be reached
}