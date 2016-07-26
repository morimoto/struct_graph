/*
 * sample.c
 *
 * Copyright (c) 2016 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This sample came from Linux Kernel ALSA SoC code
 */

struct snd_soc_card {
  struct snd_card *snd_card;

  /* CPU <--> Codec DAI links  */
  struct snd_soc_dai_link *dai_link;	/* original was list_head */
  struct snd_soc_codec_conf *codec_conf;

  /*
   * optional auxiliary devices such as amplifiers or codecs with DAI
   * link unused
   */
  const struct snd_kcontrol_new *controls;

  struct snd_soc_pcm_runtime *rtd_list;
};

struct snd_card {
};

struct snd_soc_dai_link {
  const char *cpu_name;
  struct device_node *cpu_of_node, *codec_of_node;

  const char *cpu_dai_name,  *codec_name, *codec_dai_name;

  struct snd_soc_dai_link_component *codecs;
  const struct snd_soc_pcm_stream *params;
  const struct snd_soc_ops *ops;
  const struct snd_soc_compr_ops *compr_ops;
};

struct snd_soc_pcm_stream {
};

struct snd_soc_dai_link_component {
};

struct device_node {
};

struct snd_soc_ops {
};

struct snd_soc_compr_ops {
};

struct list_head {
};

struct snd_soc_codec_conf {
};

struct snd_kcontrol_new {
};

struct snd_pcm_ops {
};

struct snd_pcm {
};

struct snd_compr {
};

struct snd_soc_codec {
  const struct snd_soc_codec_driver *driver;
  struct snd_soc_component component;
};

struct snd_soc_codec_driver {
};

struct snd_soc_platform {
  struct snd_soc_component component;
};

struct snd_soc_dai_driver {
};

struct snd_soc_dai {
  struct snd_soc_dai_driver *driver;
  struct snd_soc_codec *codec;
  struct snd_soc_component *component;
};

struct snd_soc_component {
};

struct snd_pcm_substream {
  struct snd_pcm *pcm;
  struct snd_pcm_runtime *runtime;
  struct snd_soc_pcm_runtime *private_data;		/* copied from pcm->private_data */
};

struct snd_soc_dpcm_runtime {
};

struct snd_pcm_runtime {
  struct snd_pcm_substream *trigger_master;

};

struct snd_soc_pcm_runtime {
  struct snd_soc_card *card;
  struct snd_soc_dai_link *dai_link;
  struct snd_pcm_ops ops, *ops;

  /* runtime devices */
  struct snd_pcm *pcm;
  struct snd_compr *compr;
  struct snd_soc_codec *codec;
  struct snd_soc_platform *platform;
  struct snd_soc_dai *codec_dai, cpu_dai, **codec_dais;
  struct snd_soc_component *component; /* Only valid for AUX dev rtds */
};
