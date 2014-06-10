#include "core.hpp"

void swap_endian(char* pt, bool_t byte_size)
{
	byte_size/=8;
	char buffer;
	bool_t i;
	for (i=0; i<byte_size/2; i++)
	{
		buffer=pt[i];
		pt[i]=pt[byte_size-i-1];
		pt[byte_size-i-1]=buffer;
	}
}

void WAV_header::init(unsigned n_of_samples, unsigned short bit, unsigned short ch, unsigned hz)
{
	string riff("RIFF");
	string wave("WAVE");
	string format("fmt ");
	string data("data");
	riff.copy(RIFF,4);
	ChunkSize=n_of_samples * ch * bit/8+36;
	wave.copy(WAVE,4);
	format.copy(fmt,4);
	Subchunk1Size=16;
	AudioFormat=1;
	NumOfChannels=ch;
	SamplesPerSec=hz;
	bytesPerSec=hz * ch * bit/8;
	blockAlign=ch * bit/8;
	bitsPerSample=bit;
	data.copy(Subchunk2ID,4);
	Subchunk2Size = n_of_samples * ch * bit/8;
	swap_endian((char*) &ChunkSize, sizeof(unsigned));
	swap_endian((char*) &Subchunk1Size, sizeof(unsigned));
	swap_endian((char*) &AudioFormat, sizeof(unsigned short));
	swap_endian((char*) &NumOfChannels, sizeof(unsigned short));
	swap_endian((char*) &SamplesPerSec, sizeof(unsigned));
	swap_endian((char*) &bytesPerSec, sizeof(unsigned));
	swap_endian((char*) &blockAlign, sizeof(unsigned short));
	swap_endian((char*) &bitsPerSample, sizeof(unsigned short));
	swap_endian((char*) &Subchunk2Size, sizeof(unsigned));	
}

void d2x_comp(wvector &res, wvector &x, wvector &y){
	index_t i;
	for (i=0; i<y.len()-1; i++)
	{
		//res.a[i+1]=2*(y3.a[2]/((x3.a[2]-x3.a[0])*(x3.a[2]-x3.a[1]))+y3.a[1]/((x3.a[1]-x3.a[0])*(x3.a[1]-x3.a[2]))+y3.a[0]/((x3.a[0]-x3.a[1])*(x3.a[0]-x3.a[2])));		
		res.a[i+1]=(y.a[i]+y.a[i+2]-2*y.a[i+1])/pow(x.a[i+1]-x.a[i], 2);
	}
	return;
}

void d2x2d2t( wvector &res, wvector &d2x, val_t &v2)
{
	index_t i;
	for(i=0; i<res.len(); i++)
	{
		res.a[i]=v2*d2x.a[i];
	}
	return;
}

void update_d1t(wvector &d1t, wvector &d2t, val_t &dt)
{
	index_t i;
	for (i=0; i<d1t.len(); i++)
	{
		d1t.a[i]+=d2t.a[i]*dt;
	}
	return;
}

void update_y(wvector &y, wvector &d1t, val_t &dt)
{
	index_t i;
	for(i=0; i<y.len(); i++)
	{
		y.a[i]+=d1t.a[i]*dt;
	}
}

int core(val_t v, val_t len, val_t sound_len, memory_storage m)
{
	m.head.init(sound_len*SAMPLE_RATE, 16, 1, SAMPLE_RATE);
	index_t i,j;
	val_t step = len/(m.x.l-1);
	for (i=0; i<m.x.l; i++)
	{
		m.x.a[i]=i*step;
		m.d2t.a[i]=m.d2x.a[i]=m.d1t.a[i]=0;
	}
	val_t v2, dt;
	index_t stmax;
	index_t sel=100;
	stmax=SAMPLE_NUMBER;
	
	//ofstream tunnel;
	//tunnel.open("start.dat");
	//ofstream tunnel2("wave.dat");
	ofstream out("y.wav", ofstream::binary);
	
	v2=v*v;
	dt=2*len/v/stmax;

	for (i=1; i<m.x.len(); i++)
	{
		m.y.a[i] = 2*(.25-2/M_PI/M_PI*(cos(2*M_PI*m.x.a[i]/len)+cos(2*M_PI*3*m.x.a[i]/len)/9+cos(2*M_PI*5*m.x.a[i]/len)/25+cos(7*2*M_PI*m.x.a[i]/len)/49+cos(2*M_PI*m.x.a[i]*9/len)/81));
		//m.y.a[i] = sin(M_PI*m.x.a[i]/len);
		//tunnel << m.x.a[i] << "\t" << m.y.a[i] << endl;
	}
	m.y.a[N_POINT-1]=0;
	//y.print_to_file(tunnel, 12);
	
	
	for(j=0; j<stmax; j++)
	{
		d2x_comp(m.d2x, m.x, m.y);
		d2x2d2t( m.d2t, m.d2x, v2);
		update_d1t(m.d1t, m.d2t, dt);
		update_y(m.y, m.d1t, dt);
		//cout << y.a[sel] << '\t' << d2x.a[sel] << '\t' << d2t.a[sel] << '\t'<<d1t.a[sel] << endl;
		//cout << setw(20) << d1t.a[sel];
		if (m.y.a[sel]<=1 && m.y.a[sel] >= -1)
		{
			m.result[j]=32765*m.y.a[sel];
		}
		else
		{
			if (m.y.a[sel] >0)	m.result[j]=32765;
			if (m.y.a[sel] <0)	m.result[j]=-32765;
		}
	}
	
	dt=1/dt;
	v2=dt/SAMPLE_RATE;
    	out.write( (char*) &m.head , sizeof (WAV_header));
	//cout << "sample rate: " << dt << " Hz" << "\tMin frequency:" << v/2/len <<endl;
	dt*=sound_len;
	for(v=0; v<dt ; v+=v2)
	{
		out.write( (char*)&m.result[int(round(v))%SAMPLE_NUMBER], sizeof(short signed int) );
	}
	out.close();	
	//cout << j << endl;
	//tunnel2.close();
	//tunnel.close();
	//system("sox -t raw -r 44100 -s -b 16 -c 1 y.bin y.wav");
	//system("./plot.gp -persist");
	//system("play y.wav");
	return 0;
}

memory_storage::memory_storage() : 
y(N_POINT, 0), x(N_POINT,0), d2x(N_POINT,0), d1t(N_POINT,0), d2t(N_POINT,0), head()
{
	result= new short signed int [SAMPLE_NUMBER];
}
